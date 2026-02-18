#pragma once
#include "../template.h"//or for other header files needed form template
#include <limits>
//#include <glm/common.hpp>


namespace Tmpl8
{
	class AABB
	{
	public:
		AABB() = default;
		vec2f min{ std::numeric_limits<float>::max() };
		vec2f max{ std::numeric_limits<float>::lowest() };

		AABB(const vec2f& a, const vec2f& b) noexcept
		{
			min = Min(a, b);
			max = Max(a, b);
		}

		AABB(const vec2f& a, const vec2f& b, const vec2f& c) noexcept
		{
			min = Min(a, Min(b, c));
			max = Max(a, Max(b, c));
		}
		
		AABB(const vec2f& a, const vec2f& b, const vec2f& c, const vec2f& d) noexcept
		{
			min = Min(Min(a, b), Min(c, d));
			max = Max(Max(a, b), Max(c, d));
		}

		AABB operator+(const vec2f& a) const noexcept
		{
			return { Min + a,Max + a };
		}

		AABB operator+=(const vec2f& a ) noexcept
		{
			Min += a;
			Max += a;
			return *this;
		}

		AABB operator-(const vec2f& a) const noexcept
		{
			return { Min - a,Max, - a };
		}

		AABB operator-=(const vec2f& a) noexcept
		{
			Min -= a;
			Max -= a;
			return *this;
		}

		float Width() const noexcept
		{
			return Max.x, Min.x;
		}

		float Height() const noexcept
		{
			return Max.y, Min.y;
		}
		
		float area() const noexcept
		{
			return Width() * Height();
		}

		vec2f size() const noexcept
		{
			return Max - Min;
		}

		vec2f extent() const noexcept
		{
			return size() * 0.5f;
		}
		
		AABB& expand(const vec2f p) noexcept
		{
			min = Min(min, p);
			max = Max(max, p);
			return *this;
		}

		AABB& expand(const AABB& aabb) noexcept
		{
			min = Min(min, aabb.min);
			max = Max(max, aabb.max);
			return *this;
		}

		/// is a union of 2 AABB's this shrinks the aabb
		AABB& clamp(const AABB& aabb) noexcept
		{
			min = Max(min, aabb.min);
			max = Min(max, aabb.max);
			return *this;
		}

		bool intersect(const AABB& aabb) const noexcept
		{
			if (max.x < aabb.min.x) return false;
			if (min.x > aabb.max.x) return false;
			if (max.y < aabb.min.y) return false;
			if (min.y > aabb.max.y) return false;
			return true;
		}
	};
}