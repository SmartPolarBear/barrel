//
// Created by cleve on 1/30/2022.
//

#pragma once

#include "storage/disk/disk_manager.h"
#include "buffer/replacer.h"
#include "storage/page/page.h"

#include <memory>
#include <tuple>
#include <mutex>
#include <atomic>

#include <gsl/gsl>

namespace barrel::buffer
{
class buffer_pool_manager final
{
public:
	buffer_pool_manager(size_t size,
			std::shared_ptr<storage::disk::disk_manager> dm);

	storage::page::page* fetch_page(page_id_type id);

	bool unpin_page(page_id_type id, bool dirty);

	bool flush_page(page_id_type id);

	void flush_all_pages();

	std::tuple<page_id_type, storage::page::page*> new_page();

	bool delete_page(page_id_type id);

	page_id_type allocate_page();

	void deallocate_page([[maybe_unused]] page_id_type id);

	void validate_page_id(page_id_type id);

private:

	const size_t pool_size_;

	const std::shared_ptr<storage::disk::disk_manager> disk_manager_;

	const std::unique_ptr<buffer::I_replacer> replacer_;

	std::atomic<page_id_type> next_page_id_{ 0 };

	const std::unique_ptr<storage::page::page[]> page_buf_;

	std::span<storage::page::page> pages_;

	std::unordered_map<page_id_type, frame_id_type> page_table_{};

	std::list<frame_id_type> freelist_{};

	std::mutex mut_{};
};
}
