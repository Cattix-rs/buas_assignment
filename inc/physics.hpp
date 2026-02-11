#pragma once
#include "../template.h"

namespace Tmpl8
{
	/// all small letters have their reasoning form physics 
	class physics
	{
	public:
		physics() = default;
		void Init();

		// gravity constant
		void Applyg(vec2f& v, float deltaTime) const;

		// position calculation
		vec2f IntegratePosition(const vec2f& prevPos, const vec2f& v, float deltaTime) const;

	private:
		vec2f g{ 0.0f, 0.0f };
		
	};
}