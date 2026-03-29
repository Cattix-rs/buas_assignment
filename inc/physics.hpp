#pragma once
#include "../template.h"
#include "player.hpp"


namespace Tmpl8
{
	///also will use these files as math places for sprite related thins
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

		static void ResolvePlayerCollision(Player& player, const Level& level, float deltaTime, int activePhase);
		void CheckPickupCollision(Player& player, Level& level);

	private:
		vec2f g{ 0.0f, 0.0f };
		
	};
}