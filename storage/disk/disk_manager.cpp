//
// Created by cleve on 1/22/2022.
//

#include "storage/disk/disk_manager.h"

using namespace std;

barrel::storage::disk::disk_manager::disk_manager(std::string name)
		: db_name_(std::move(name)),
		  log_name(db_name_ + ".log")
{
	log_stream_.open(log_name, ios::binary | ios::in | ios::app | ios::out);

	// create if not exist
	if (!log_stream_.is_open())
	{
		log_stream_.clear();

		log_stream_.open(log_name, ios::binary | ios::trunc | ios::app | ios::out);
		log_stream_.close();

		log_stream_.open(log_name, ios::binary | ios::in | ios::app | ios::out);

		if (!log_stream_.is_open())
		{

		}
	}
}
