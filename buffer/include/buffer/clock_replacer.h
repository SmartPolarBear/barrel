//
// Created by cleve on 1/30/2022.
//

#pragma once

#include "types.h"

#include "buffer/replacer.h"

namespace barrel::buffer
{
class clock_replacer final : public I_replacer
{

public:
	[[nodiscard]] std::optional<frame_id_type> victim() override;

	void pin(frame_id_type id) override;

	void unpin(frame_id_type id) override;

	[[nodiscard]] size_t size() const override;
};
}
