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

/// \brief disk manager manages all writes and reads
class disk_manager final
{
public:
	[[nodiscard]] explicit disk_manager(std::string name);

	/// shutdown the disk manager
	void shutdown();

	/// write pages to db file
	/// \param pid
	/// \param data
	void write_page(page_id_type pid, byte_span data);

	/// read pages to db file
	/// \param pid
	/// \param data the data buffer to read to
	void read_page(page_id_type pid, byte_span data);

	/// write data to log
	/// \param data
	void write_log(byte_span data);

	/// read to data from offset
	/// \param data
	/// \param offset
	void read_log(byte_span data, offset_type offset);

	[[nodiscard]] size_t get_write_count() const;

	[[nodiscard]] size_t get_flush_count() const;

	[[nodiscard]] bool get_flush_state() const;

private:
	static inline void
	open_or_create_stream(std::fstream& stream,
			std::ios_base::openmode mode,
			std::ios_base::openmode create_mode,
			const std::string& name);

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

	bool flush_log_{ false };

	std::mutex mut_;
};
}
