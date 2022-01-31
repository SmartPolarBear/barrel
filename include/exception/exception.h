//
// Created by cleve on 1/27/2022.
//

// custom exceptions for barrel project

#pragma once

#include <iostream>
#include <format>
#include <string>
#include <exception>
#include <stdexcept>

namespace barrel::exceptions
{
enum class exception_type
{
	MIN = 0,

	INVALID,

	OUT_OF_RANGE,
	CONVERSION,
	UNKNOWN_TYPE,
	DECIMAL,
	MISMATCH_TYPE,
	DIVIDE_BY_0,
	OUT_OF_MEMORY,
	NOT_IMPLEMENT,

	MAX
};

class exception : public std::runtime_error
{
public:
	[[nodiscard]] explicit exception(const std::string& msg) : std::runtime_error(msg), type_(exception_type::INVALID)
	{
		std::cerr << std::format("Message : {}", msg);
	}

	[[nodiscard]] exception(const std::string& msg, exception_type t) : std::runtime_error(msg), type_(t)
	{
		std::cerr << std::format("Type : {}\nMessage : {}", t, msg);
	}

	exception_type type() const
	{
		return type_;
	}

private:
	exception_type type_{ exception_type::INVALID };
};

class [[maybe_unused]] not_implemented final : public exception
{
public:
	not_implemented() = delete;

	[[nodiscard]] explicit not_implemented(const std::string& msg) : exception(msg, exception_type::NOT_IMPLEMENT)
	{
	}
};

}


#include <magic_enum.hpp>

namespace magic_enum
{
template<>
struct customize::enum_range<barrel::exceptions::exception_type>
{
	static constexpr int min = (int)barrel::exceptions::exception_type::MIN;
	static constexpr int max = (int)barrel::exceptions::exception_type::MAX;
};
}

namespace std
{
template<>
struct std::formatter<barrel::exceptions::exception_type> : std::formatter<std::string>
{
	auto format(barrel::exceptions::exception_type t, format_context& ctx)
	{
		return formatter<string>::format(string{ magic_enum::enum_name(t) }, ctx);
	}
};
}