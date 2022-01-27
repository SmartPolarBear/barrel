//
// Created by cleve on 1/22/2022.
//

#include "storage/disk/disk_manager.h"
#include "exception/exception.h"

#include <mutex>

using namespace std;

barrel::storage::disk::disk_manager::disk_manager(std::string name)
		: db_name_(std::move(name)),
		  log_name_(db_name_ + ".log")
{
	lock_guard g{ mut_ };

	open_or_create_stream(log_stream_, log_name_);
	open_or_create_stream(db_stream_, db_name_);
}

void barrel::storage::disk::disk_manager::open_or_create_stream(fstream& stream, const std::string& name)
{
	stream.open(name, ios::binary | ios::in | ios::app | ios::out);

	// create if not exist
	if (!stream.is_open())
	{
		stream.clear();

		stream.open(name, ios::binary | ios::trunc | ios::app | ios::out);
		stream.close();

		stream.open(name, ios::binary | ios::in | ios::app | ios::out);

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

void barrel::storage::disk::disk_manager::write_page(barrel::page_id_type pid, std::span<uint8_t> data)
{

}

void barrel::storage::disk::disk_manager::read_page(barrel::page_id_type pid, std::span<uint8_t> data)
{

}

void barrel::storage::disk::disk_manager::write_log(std::span<uint8_t> data)
{

}

void barrel::storage::disk::disk_manager::read_log(std::span<uint8_t> data, barrel::offset_type offset)
{

}
