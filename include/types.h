//
// Created by cleve on 1/26/2022.
//

// all types that are used globally

#pragma once

#include <cstdint>

namespace barrel
{

using offset_type = int64_t;

// the id of page
using page_id_type = int64_t;
static inline constexpr page_id_type INVALID_PAGE_ID = -1;
}