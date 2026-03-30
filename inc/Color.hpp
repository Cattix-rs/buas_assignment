#pragma once
#include <cassert>
#include <cstdint>
#include <string_view>

#include "AABB.hpp"


namespace Atlas
{
	union Color
	{
		constexpr Color() noexcept;

		constexpr explicit Color(uint32_t rgba) noexcept;

		constexpr Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255u)noexcept;

		~Color() noexcept = default;
		constexpr Color(const Color&) noexcept = default;
		constexpr Color(Color&&) noexcept = default;
		constexpr Color& operator=(const Color&) = default;
		constexpr Color& operator=(Color&&) = default;

		constexpr auto operator<=>(const Color& rhs) const noexcept;
		constexpr bool operator==(const Color& rhs) const noexcept;

		Color operator+(const Color& rhs) const noexcept;
		Color& operator+=(const Color& rhs) noexcept;
		Color operator-(const Color& rhs) const noexcept;
		Color& operator-=(const Color& rhs) noexcept;
		Color operator*(const Color& rhs) const noexcept;
		Color& operator*=(const Color& rhs) noexcept;
		Color operator*(float rhs) const noexcept;
		Color& operator*=(float rhs) noexcept;
		Color operator/(float rhs) const noexcept;
		Color& operator/=(float rhs) noexcept;

		constexpr Color withAlpha(uint8_t alpha) const noexcept;

		constexpr Color withAlpha(float alpha) const noexcept;

		static constexpr Color fromFloats(float r, float g, float b, float a = 1.0f) noexcept;

		static constexpr Color fromHex(uint32_t color) noexcept;

		static Color fromHTML(std::string_view html);

		static inline Color fromHSV(float H, float S = 1.0f, float V = 1.0f) noexcept;

		uint32_t rgba;
		struct RGBA
		{
			uint8_t r;
			uint8_t g;
			uint8_t b;
			uint8_t a;
		} channels;

		static constexpr uint32_t RedMask = 0x000000FF;
		static constexpr uint32_t GreenMask = 0x0000FF00;
		static constexpr uint32_t BlueMask = 0x00FF0000;
		static constexpr uint32_t AlphaMask = 0xFF000000;

        static constexpr uint32_t RedShift = 0;
        static constexpr uint32_t GreenShift = 8;
        static constexpr uint32_t BlueShift = 16;
        static constexpr uint32_t AlphaShift = 24;

        static const Color AliceBlue;
        static const Color AntiqueWhite;
        static const Color Aqua;
        static const Color AquaMarine;
        static const Color Azure;
        static const Color Beige;
        static const Color Bisque;
        static const Color Black;
        static const Color BlanchedAlmond;
        static const Color Blue;
        static const Color BlueViolet;
        static const Color Brown;
        static const Color BurlyWood;
        static const Color CadetBlue;
        static const Color Chartreuse;
        static const Color Chocolate;
        static const Color Coral;
        static const Color CornflowerBlue;
        static const Color Cornsilk;
        static const Color Crimson;
        static const Color Cyan;
        static const Color DarkBlue;
        static const Color DarkCyan;
        static const Color DarkGoldenRod;
        static const Color DarkGray;
        static const Color DarkGrey;
        static const Color DarkGreen;
        static const Color DarkKhaki;
        static const Color DarkMagenta;
        static const Color DarkOliveGreen;
        static const Color DarkOrange;
        static const Color DarkOrchid;
        static const Color DarkRed;
        static const Color DarkSalmon;
        static const Color DarkSeaGreen;
        static const Color DarkSlateBlue;
        static const Color DarkSlateGray;
        static const Color DarkSlateGrey;
        static const Color DarkTurquoise;
        static const Color DarkViolet;
        static const Color DeepPink;
        static const Color DeepSkyBlue;
        static const Color DimGray;
        static const Color DimGrey;
        static const Color DodgerBlue;
        static const Color FireBrick;
        static const Color FloralWhite;
        static const Color ForestGreen;
        static const Color Fuchsia;
        static const Color Gainsboro;
        static const Color GhostWhite;
        static const Color Gold;
        static const Color GoldenRod;
        static const Color Gray;
        static const Color Grey;
        static const Color Green;
        static const Color GreenYellow;
        static const Color HoneyDew;
        static const Color HotPink;
        static const Color IndianRed;
        static const Color Indigo;
        static const Color Ivory;
        static const Color Khaki;
        static const Color Lavender;
        static const Color LavenderBlush;
        static const Color LawnGreen;
        static const Color LemonChiffon;
        static const Color LightBlue;
        static const Color LightCoral;
        static const Color LightCyan;
        static const Color LightGoldenRodYellow;
        static const Color LightGray;
        static const Color LightGrey;
        static const Color LightGreen;
        static const Color LightPink;
        static const Color LightSalmon;
        static const Color LightSeaGreen;
        static const Color LightSkyBlue;
        static const Color LightSlateGray;
        static const Color LightSlateGrey;
        static const Color LightSteelBlue;
        static const Color LightYellow;
        static const Color Lime;
        static const Color LimeGreen;
        static const Color Linen;
        static const Color Magenta;
        static const Color Maroon;
        static const Color MediumAquaMarine;
        static const Color MediumBlue;
        static const Color MediumOrchid;
        static const Color MediumPurple;
        static const Color MediumSeaGreen;
        static const Color MediumSlateBlue;
        static const Color MediumSpringGreen;
        static const Color MediumTurquoise;
        static const Color MediumVioletRed;
        static const Color MidnightBlue;
        static const Color MintCream;
        static const Color MistyRose;
        static const Color Moccasin;
        static const Color NavajoWhite;
        static const Color Navy;
        static const Color OldLace;
        static const Color Olive;
        static const Color OliveDrab;
        static const Color Orange;
        static const Color OrangeRed;
        static const Color Orchid;
        static const Color PaleGoldenRod;
        static const Color PaleGreen;
        static const Color PaleTurquoise;
        static const Color PaleVioletRed;
        static const Color PapayaWhip;
        static const Color PeachPuff;
        static const Color Peru;
        static const Color Pink;
        static const Color Plum;
        static const Color PowderBlue;
        static const Color Purple;
        static const Color RebeccaPurple;
        static const Color Red;
        static const Color RosyBrown;
        static const Color RoyalBlue;
        static const Color SaddleBrown;
        static const Color Salmon;
        static const Color SandyBrown;
        static const Color SeaGreen;
        static const Color Seashell;
        static const Color Sienna;
        static const Color Silver;
        static const Color SkyBlue;
        static const Color SlateBlue;
        static const Color SlateGray;
        static const Color SlateGrey;
        static const Color Snow;
        static const Color SpringGreen;
        static const Color SteelBlue;
        static const Color Tan;
        static const Color Teal;
        static const Color Thistle;
        static const Color Tomato;
        static const Color Turquoise;
        static const Color Violet;
        static const Color Wheat;
        static const Color White;
        static const Color WhiteSmoke;
        static const Color Yellow;
        static const Color YellowGreen;
    };
    constexpr Color::Color() noexcept
        : channels{ 0, 0, 0, 255 }
    {}

    constexpr Color::Color(uint32_t rgba) noexcept
        : rgba{ rgba }
    {}

    constexpr Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) noexcept
        : channels{ r, g, b, a }
    {}

    constexpr bool Color::operator==(const Color& rhs) const noexcept
    {
        return rgba == rhs.rgba;
    }

    constexpr auto Color::operator<=>(const Color& rhs) const noexcept
    {
        if (const auto cmp = channels.r <=> rhs.channels.r; cmp != 0)
            return cmp;
        if (const auto cmp = channels.g <=> rhs.channels.g; cmp != 0)
            return cmp;
        if (const auto cmp = channels.b <=> rhs.channels.b; cmp != 0)
            return cmp;

        return channels.a <=> rhs.channels.a;
    }
    inline Color Color::operator+(const Color& rhs) const noexcept
    {
        const auto red = static_cast<uint8_t>(Tmpl8::Min(channels.r + rhs.channels.r, 255));
        const auto green = static_cast<uint8_t>(Tmpl8::Min(channels.g + rhs.channels.g, 255));
        const auto blue = static_cast<uint8_t>(Tmpl8::Min(channels.b + rhs.channels.b, 255));
        const auto alpha = static_cast<uint8_t>(Tmpl8::Min(channels.a + rhs.channels.a, 255));

        return { red, green, blue, alpha };
    }

    inline Color& Color::operator+=(const Color& rhs) noexcept
    {
        *this = *this + rhs;
        return *this;
    }

    inline Color Color::operator-(const Color& rhs) const noexcept
    {
        const auto red = static_cast<uint8_t>(Tmpl8::Max(channels.r - rhs.channels.r, 0));
        const auto green = static_cast<uint8_t>(Tmpl8::Max(channels.g - rhs.channels.g, 0));
        const auto blue = static_cast<uint8_t>(Tmpl8::Max(channels.b - rhs.channels.b, 0));
        const auto alpha = static_cast<uint8_t>(Tmpl8::Max(channels.a - rhs.channels.a, 0));

        return { red, green, blue, alpha };
    }

    inline Color& Color::operator-=(const Color& rhs) noexcept
    {
        *this = *this - rhs;
        return *this;
    }

    inline Color Color::operator*(const Color& rhs) const noexcept
    {
        const auto red = static_cast<uint8_t>(channels.r * rhs.channels.r / 255);
        const auto green = static_cast<uint8_t>(channels.g * rhs.channels.g / 255);
        const auto blue = static_cast<uint8_t>(channels.b * rhs.channels.b / 255);
        const auto alpha = static_cast<uint8_t>(channels.a * rhs.channels.a / 255);

        return { red, green, blue, alpha };
    }

    inline Color& Color::operator*=(const Color& rhs) noexcept
    {
        *this = *this * rhs;
        return *this;
    }

    inline Color Color::operator*(float rhs) const noexcept
    {
        const auto red = static_cast<uint8_t>(Tmpl8::Clamp(static_cast<float>(channels.r) * rhs, 0.0f, 255.0f));
        const auto green = static_cast<uint8_t>(Tmpl8::Clamp(static_cast<float>(channels.g) * rhs, 0.0f, 255.0f));
        const auto blue = static_cast<uint8_t>(Tmpl8::Clamp(static_cast<float>(channels.b) * rhs, 0.0f, 255.0f));
        const auto alpha = static_cast<uint8_t>(Tmpl8::Clamp(static_cast<float>(channels.a) * rhs, 0.0f, 255.0f));

        return { red, green, blue, alpha };
    }

    inline Color& Color::operator*=(float rhs) noexcept
    {
        *this = *this * rhs;
        return *this;
    }

    inline Color Color::operator/(float rhs) const noexcept
    {
        assert(rhs != 0.0f);

        rhs = 1.0f / rhs;

        return operator*(rhs);
    }

    inline Color& Color::operator/=(float rhs) noexcept
    {
        assert(rhs != 0.0f);

        rhs = 1.0f / rhs;

        return operator*=(rhs);
    }

}
