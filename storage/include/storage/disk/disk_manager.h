//
// Created by cleve on 1/22/2022.
//

// disk manager manages the database file

#pragma once

#include "types.h"
#include "config.h"

#include <fstream>
#include <mutex>
#include <assert.h>

namespace barrel::storage::disk
{

class disk_manager final
{
public:
	[[nodiscard]] explicit disk_manager(std::string name);


private:
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

	std::string db_name_, log_name;

	std::mutex mut_;
};
}
