//
// Created by cleve on 1/30/2022.
//

#include "buffer/clock_replacer.h"

using namespace barrel;

using namespace std;

std::optional<frame_id_type> barrel::buffer::clock_replacer::victim()
{
	return std::optional<frame_id_type>();
}

void barrel::buffer::clock_replacer::pin(barrel::frame_id_type id)
{

}

void barrel::buffer::clock_replacer::unpin(barrel::frame_id_type id)
{

}

size_t barrel::buffer::clock_replacer::size() const
{
	return 0;
}
