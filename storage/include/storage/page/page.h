//
// Created by cleve on 1/31/2022.
//

#pragma once

#include "types.h"
#include "config.h"

#include <shared_mutex>

namespace barrel::storage::page
{
class page
{
public:
	page();

	~page() = default;

	[[nodiscard]] inline byte_span data()
	{
		return byte_span{ data_ };
	}

	[[nodiscard]] inline page_id_type id() const
	{
		return id_;
	}

	[[nodiscard]] inline size_t pin_count() const
	{
		return pin_count_;
	}

	[[nodiscard]] inline bool dirty() const
	{
		return dirty_;
	}

	[[nodiscard]] std::shared_mutex& lock()
	{
		return mut_;
	}

	[[nodiscard]] inline lsn_type get_lsn() const
	{
		return *reinterpret_cast<const lsn_type*>(data_ + OFFSET_LSN);
	}

	inline void set_lsn(lsn_type t)
	{
		*reinterpret_cast<lsn_type*>(data_ + OFFSET_LSN) = t;
	}

protected:

	static inline constexpr size_t SIZE_HEADER = 8;

	static inline constexpr size_t OFFSET_PAGE_START = 0;
	static inline constexpr size_t OFFSET_LSN = 4;

private:
	inline void reset();

	char data_[PAGE_SIZE]{};

	page_id_type id_{ INVALID_PAGE_ID };

	size_t pin_count_{ 0 };

	bool dirty_{ false };

	std::shared_mutex mut_{};
};
}