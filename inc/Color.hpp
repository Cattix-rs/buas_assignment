#pragma once
#include <cstdint>

namespace Atlas
{
	union Color
	{
		constexpr Color() noexcept;

		constexpr explicit Color(uint32_t rgba) noexcept;

		constexpr Color(uint8_t r, uint8_t g, int8_t b, uint8_t a = 255u)noexcept;

		~Color() noexcept = default;
		constexpr Color(const Color&) noexcept = default;
		constexpr Color(Color&&) noexcept = default;
		constexpr Color& operator=(const Color&) = default;
		constexpr Color& operator=(Color&&) = default;

		constexpr auto operator<=>(const Color& rhs) const noexcept;
		constexpr bool operator==(const Color& rhs) const noexcept;

		Color operator+(const Color& rhs) const noexcept;
		Color& operator+=(const Color& rhs) noexcept;
	};
}
