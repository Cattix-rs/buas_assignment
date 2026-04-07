#pragma once

#include <cstdint>

namespace Tmpl8
{
	template<typename T>
	struct Rect
	{
		T left = T(0);
		T top = T(0);
		T width = T(0);
		T height = T(0);
	};
	using RectI = Rect<int32_t>;
	using RectUI = Rect<uint32_t>;
	using RectF = Rect<float>;
	using RectD = Rect<double>;
}
