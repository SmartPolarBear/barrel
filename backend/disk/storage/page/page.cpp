//
// Created by cleve on 1/31/2022.
//

#include "storage/page/page.h"

barrel::storage::page::page::page()
{
	reset();
}

void barrel::storage::page::page::reset()
{
	memset(data_, 0, PAGE_SIZE);
}
