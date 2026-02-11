#include <physics.hpp>

#include "../template.h"


namespace Tmpl8
{
	void physics::Init()
	{
		g = vec2f{ 0.0f, 0.0000f };
	}

	void physics::Applyg(vec2f& v, float deltaTime) const
	{
		v.y += g.y * deltaTime;
	}

	vec2f physics::IntegratePosition(const vec2f& prevPos, const vec2f& v, float deltaTime) const
	{
		return prevPos + v * deltaTime;
	}
}
