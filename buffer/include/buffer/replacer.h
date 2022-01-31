//
// Created by cleve on 1/30/2022.
//

// interface for a replacer

#pragma once

#include "types.h"

#include <optional>

namespace barrel::buffer
{
/// interface for a replacer
class I_replacer
{
public:
	I_replacer() = default;

	virtual ~I_replacer() = default;

	/// find a frame to be the victim
	/// \return
	[[nodiscard]] virtual std::optional<frame_id_type> victim() = 0;

	/// pin a frame to ensure it will not be a victim
	/// \param id
	virtual void pin(frame_id_type id) = 0;

	/// unpin a page to make it possible to be a victim
	/// \param id
	virtual void unpin(frame_id_type id) = 0;

	/// the number of frames which can be a victim
	/// \return
	[[nodiscard]] virtual size_t size() const = 0;
};
}
