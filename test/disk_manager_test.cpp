//
// Created by cleve on 1/29/2022.
//

#include "types.h"

#include "storage/disk/disk_manager.h"
#include "exception/exception.h"

#include <string_view>

#include <gtest/gtest.h>

using namespace barrel;

using namespace std;
using namespace std::literals;

class disk_manager_test : public testing::Test
{
public:
	static constexpr auto DB_NAME = "test.db"sv;
	static constexpr auto LOG_NAME = "test.db.log"sv;

protected:
	void SetUp() override
	{
		remove(DB_NAME.data());
		remove(LOG_NAME.data());
	}

	void TearDown() override
	{
		remove(DB_NAME.data());
		remove(LOG_NAME.data());
	}


};

TEST_F(disk_manager_test, PageReadWrite)
{
	char buf[barrel::PAGE_SIZE]{ 0 }, data[barrel::PAGE_SIZE]{ 0 };
	strncpy(data, "test str str str", sizeof(data));

	barrel::storage::disk::disk_manager dm{ DB_NAME.data() };

	// empty read
	dm.read_page(0, byte_span{ buf });
	EXPECT_EQ(all_of(buf, buf + PAGE_SIZE, [](char c)
	{ return c == 0; }), true);

	// write and read at 0
	dm.write_page(0, byte_span{ data });
	dm.read_page(0, byte_span{ buf });
	EXPECT_EQ(strncmp(buf, data, sizeof(data)), 0);

	// write and read at 5
	memset(buf, 0, sizeof(buf));

	dm.write_page(5, byte_span{ data });
	dm.read_page(5, byte_span{ buf });
	EXPECT_EQ(strncmp(buf, data, sizeof(data)), 0);
}

TEST_F(disk_manager_test, LogReadWrite)
{
	char buf[barrel::PAGE_SIZE]{ 0 }, data[barrel::PAGE_SIZE]{ 0 };
	strncpy(data, "log message str", sizeof(data));

	barrel::storage::disk::disk_manager dm{ DB_NAME.data() };

	// empty read
	dm.read_log(byte_span{ buf }, 0);
	EXPECT_EQ(all_of(buf, buf + PAGE_SIZE, [](char c)
	{ return c == 0; }), true);

	// write and read
	dm.write_log(byte_span{ data });
	dm.read_log(byte_span{ buf }, 0);
	EXPECT_EQ(strncmp(buf, data, sizeof(data)), 0);
}

