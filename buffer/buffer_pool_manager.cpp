//
// Created by cleve on 1/30/2022.
//

#include "buffer/buffer_pool_manager.h"
#include "buffer/clock_replacer.h"

using namespace barrel;

using namespace gsl;
using namespace std;

barrel::buffer::buffer_pool_manager::buffer_pool_manager(size_t size, std::shared_ptr<storage::disk::disk_manager> dm)
		: pool_size_(size),
		  disk_manager_(std::move(dm)),
		  replacer_(make_unique<clock_replacer>(size)),
		  page_buf_(make_unique<storage::page::page[]>(size)),
		  pages_(page_buf_.get(), size)
{
	for (size_t i = 0; i < size; i++)
	{
		freelist_.emplace_back(static_cast<frame_id_type>(i));
	}
}

barrel::storage::page::page* barrel::buffer::buffer_pool_manager::fetch_page(barrel::page_id_type id)
{
	return nullptr;
}

bool barrel::buffer::buffer_pool_manager::unpin_page(barrel::page_id_type id, bool dirty)
{
	return false;
}

bool barrel::buffer::buffer_pool_manager::flush_page(barrel::page_id_type id)
{
	return false;
}

void barrel::buffer::buffer_pool_manager::flush_all_pages()
{

}

std::tuple<page_id_type, storage::page::page*> barrel::buffer::buffer_pool_manager::new_page()
{
	return std::tuple<page_id_type, storage::page::page*>();
}

bool barrel::buffer::buffer_pool_manager::delete_page(barrel::page_id_type id)
{
	return false;
}

barrel::page_id_type barrel::buffer::buffer_pool_manager::allocate_page()
{
	return 0;
}

void barrel::buffer::buffer_pool_manager::deallocate_page(barrel::page_id_type id)
{

}

void barrel::buffer::buffer_pool_manager::validate_page_id(barrel::page_id_type id)
{

}
