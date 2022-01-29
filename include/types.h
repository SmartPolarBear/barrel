//
// Created by cleve on 1/26/2022.
//

// all types that are used globally

#pragma once

#include <cstdint>
#include <span>

#include <gsl/gsl>

namespace barrel
{

using gsl::index;

using byte_span = std::span<char>;

using offset_type = int64_t;

// the id of page
using page_id_type = int64_t;
static inline constexpr page_id_type INVALID_PAGE_ID = -1;
}