//
// Created by cleve on 1/30/2022.
//

#pragma once

#include "storage/disk/disk_manager.h"

#include <memory>

#include <gsl/gsl>

namespace barrel::buffer
{
class buffer_pool_manager final
{
public:
	buffer_pool_manager(size_t size,
			std::shared_ptr<storage::disk::disk_manager> dm);



	bool flush_page(page_id_type id);

	void flush_all_pages();


};
}
