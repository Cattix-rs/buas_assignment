#pragma once
#include <cstdint>

namespace Atlas
{
	union Color
	{
		constexpr Color() noexcept;

		constexpr explicit Color(uint32_t rgba) noexcept;


	};
}
