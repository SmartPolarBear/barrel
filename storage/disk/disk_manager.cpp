//
// Created by cleve on 1/22/2022.
//

#include "storage/disk/disk_manager.h"
#include "exception/exception.h"

#include <plog/Log.h>

#include <filesystem>

#include <gsl/assert>


using namespace std;

static char* last_buf;

barrel::storage::disk::disk_manager::disk_manager(std::string name)
		: db_name_(std::move(name)),
		  log_name_(db_name_ + ".log")
{
	lock_guard g{ mut_ };

	open_or_create_stream(log_stream_, std::ios::binary | std::ios::in | std::ios::app | std::ios::out, log_name_);
	open_or_create_stream(db_stream_, std::ios::binary | std::ios::in | std::ios::out, db_name_);

	last_buf = nullptr;
}

void barrel::storage::disk::disk_manager::open_or_create_stream(fstream& stream, ios_base::openmode mode,
		const std::string& name)
{
	stream.open(name, mode);

	// create if not exist
	if (!stream.is_open())
	{
		stream.clear();

		stream.open(name, ios::binary | ios::trunc | ios::out);
		stream.close();

		stream.open(name, mode);

		if (!stream.is_open())
		{
			throw barrel::exceptions::exception{ std::format("Cannot open file {} ", name) };
		}
	}
}

void barrel::storage::disk::disk_manager::shutdown()
{
	lock_guard g{ mut_ };

	log_stream_.close();
	db_stream_.close();
}

void barrel::storage::disk::disk_manager::write_page(barrel::page_id_type pid, byte_span data)
{
	Expects(data.size() >= PAGE_SIZE);

	const auto offset = PAGE_ID_TO_OFFSET(pid);

	lock_guard g{ mut_ };

	statistics_.writes_++;

	db_stream_.seekp(offset);
	db_stream_.write(data.data(), PAGE_SIZE);

	if (db_stream_.bad())// unrecoverable error
	{
		LOG_DEBUG << "I/O error when writing page";
		return;
	}

	db_stream_.flush();
}

void barrel::storage::disk::disk_manager::read_page(barrel::page_id_type pid, byte_span data)
{
	Expects(data.size() >= PAGE_SIZE);

	const auto offset = PAGE_ID_TO_OFFSET(pid);
	if (offset > filesystem::file_size(db_name_))
	{
		LOG_DEBUG << "Read page past the end of the file";
		return;
	}

	lock_guard g{ mut_ };

	db_stream_.seekg(offset);
	db_stream_.read(data.data(), PAGE_SIZE);
	if (db_stream_.bad()) // unrecoverable error
	{
		LOG_DEBUG << "I/O error when reading page";
		return;
	}

	const auto read_count = db_stream_.gcount();
	if (read_count < data.size())
	{
		LOG_DEBUG << "No enough data to read";
		db_stream_.clear();
		for (auto iter = data.begin() + read_count; iter != data.end(); iter++)
		{
			*iter = 0;
		}
	}
}

void barrel::storage::disk::disk_manager::write_log(byte_span data)
{
	Expects(last_buf != reinterpret_cast<char*>(data.data()));

	last_buf = reinterpret_cast<char*>(data.data());

	if (data.empty())return;

	flush_log_ = true;

	statistics_.writes_++;
	log_stream_.write(data.data(), data.size());

	if (log_stream_.bad())// unrecoverable error
	{
		LOG_DEBUG << "I/O error when writing log";
		return;
	}

	log_stream_.flush();
	flush_log_ = false;
}

void barrel::storage::disk::disk_manager::read_log(byte_span data, barrel::offset_type offset)
{
	if (data.empty())return;
	if (offset > filesystem::file_size(log_name_))
	{
		LOG_DEBUG << "Read log past the end of the file";
		return;
	}

	log_stream_.seekg(offset);
	log_stream_.read(data.data(), data.size());

	if (log_stream_.bad())// unrecoverable error
	{
		LOG_DEBUG << "I/O error when reading log";
		return;
	}

	const auto read_count = log_stream_.gcount();
	if (read_count < data.size())
	{
		LOG_DEBUG << "No enough data to read log";
		db_stream_.clear();
		for (auto iter = data.begin() + read_count; iter != data.end(); iter++)
		{
			*iter = 0;
		}
	}
}

size_t barrel::storage::disk::disk_manager::get_write_count() const
{
	return statistics_.writes_;
}

size_t barrel::storage::disk::disk_manager::get_flush_count() const
{
	return statistics_.flushes_;
}

bool barrel::storage::disk::disk_manager::get_flush_state() const
{
	return flush_log_;
}
