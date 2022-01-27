//
// Created by cleve on 1/22/2022.
//

// disk manager manages the database file

#pragma once

#include "types.h"
#include "config.h"

#include <fstream>
#include <mutex>
#include <span>
#include <cassert>

namespace barrel::storage::disk
{

class disk_manager final
{
public:
	[[nodiscard]] explicit disk_manager(std::string name);

	void shutdown();

	/// write a page to db file
	/// \param pid
	/// \param data
	void write_page(page_id_type pid, std::span<uint8_t> data);

	/// write a page to db file
	/// \param pid
	/// \param data
	void read_page(page_id_type pid, std::span<uint8_t> data);

	/// write data to log
	/// \param data
	void write_log(std::span<uint8_t> data);

	/// read to data from offset
	/// \param data
	/// \param offset
	void read_log(std::span<uint8_t> data, offset_type offset);

private:
	static inline void open_or_create_stream(std::fstream& stream, const std::string& name);

	static inline constexpr offset_type PAGE_ID_TO_OFFSET(page_id_type id)
	{
		return id * PAGE_SIZE;
	}

	struct
	{
		size_t writes_;
		size_t flushes_;
	} statistics_{ 0, 0 };

	std::fstream db_stream_{}, log_stream_{};

	std::string db_name_, log_name_;

	std::mutex mut_;
};
}
