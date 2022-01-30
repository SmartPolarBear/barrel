//
// Created by cleve on 1/30/2022.
//

#include "buffer/clock_replacer.h"

using namespace barrel;

using namespace std;

buffer::clock_replacer::clock_replacer(size_t capacity)
		: frames_(capacity + 1/*slot 0 is unused*/), capacity_(capacity)
{
	Ensures(frames_.size() == capacity_);
}

std::optional<frame_id_type> barrel::buffer::clock_replacer::victim()
{
	if (size_ == 0) // no page is under control of the replacer
	{
		return nullopt;
	}

	lock_guard g{ mut_ };
	while (size_ > 0)
	{
		auto& frame = frames_.at(hand_);
		const auto id = hand_ + 1;

		hand_++;
		hand_ %= capacity_;

		if (frame.present)
		{
			if (!frame.ref)
			{
				frame.present = false;
				size_--;
				return id;
			}
			frame.ref = false;
		}
	}

	Ensures(size_ >= 0);

	return nullopt;
}

void barrel::buffer::clock_replacer::pin(barrel::frame_id_type id)
{
	Expects(id <= capacity_);
	lock_guard g{ mut_ };
	if (frames_[id].present)
	{
		frames_[id].present = false;
		size_--;
	}
}

void barrel::buffer::clock_replacer::unpin(barrel::frame_id_type id)
{
	Expects(id <= capacity_);
	lock_guard g{ mut_ };
	if (!frames_[id].present)
	{
		frames_[id].present = true;
		size_++;
	}
	frames_[id].ref = true;
}

size_t barrel::buffer::clock_replacer::size() const
{
	return size_;
}

