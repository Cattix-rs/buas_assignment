#include <physics.hpp>

#include "../template.h"


namespace Tmpl8
{
	void physics::Init()
	{
		g = vec2f{ 0.0f, 10.0f };
	}

	void physics::Applyg(vec2f& v, float deltaTime) const
	{
		v.y += g.y * deltaTime;
	}

	vec2f physics::IntegratePosition(const vec2f& prevPos, const vec2f& v, float deltaTime) const
	{
		return vec2f(prevPos.x + v.x * deltaTime, prevPos.y + v.y * deltaTime);
	}
}
