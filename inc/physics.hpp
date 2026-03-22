#pragma once
#include "../template.h"
#include "player.hpp"


namespace Tmpl8
{
	class Game;
	class Level;
	/// all small letters have their reasoning form physics 
	class Physics
	{
	public:
		Physics() = default;
		void Init();

		// gravity constant
		void Applyg(vec2f& v, float deltaTime) const;

		// position calculation
		vec2f IntegratePosition(const vec2f& prevPos, const vec2f& v, float deltaTime) const;

		static void ResolvePlayerCollision(Player& player, const Level& level, float deltaTime, int activePhase);
		void CheckPickupCollision(Player& player, Level& level);

	private:
		vec2f g{ 0.0f, 0.0f };
		
	};
}