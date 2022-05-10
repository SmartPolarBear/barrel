//
// Created by cleve on 1/30/2022.
//

// implementation of the clock replacer

#pragma once

#include "types.h"

#include "buffer/replacer.h"

#include <mutex>

namespace barrel::buffer
{
class clock_replacer final : public I_replacer
{

public:
	[[nodiscard]] explicit clock_replacer(size_t capacity);

	[[nodiscard]] std::optional<frame_id_type> victim() override;

	void pin(frame_id_type id) override;

	void unpin(frame_id_type id) override;

	/// Intended for tests: return the reference bit of id
	/// \param id
	/// \return
	[[nodiscard]] inline int reference(frame_id_type id) const
	{
		Expects(id <= capacity_);
		return frames_[id].ref;
	}

	[[nodiscard]] size_t size() const override;

private:

	struct frame
	{
		bool ref;
		bool present;
	};

	std::vector<frame> frames_;

	int64_t hand_{ 0 };

	int64_t size_{ 0 };

	std::mutex mut_;

	const size_t capacity_;
};
}
