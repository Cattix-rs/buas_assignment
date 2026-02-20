#pragma once
#include "AABB.hpp"
#include "../surface.h"
#include "../template.h"

namespace Tmpl8
{
	class Player
	{
	public:
		Player() = default;
		// Initialize movement/animation system with the sprite and position pointers.
		void Init(Sprite* sprite, int px = 0, int py = 0);

		// Called each frame to handle input, movement and animation timing.
		void Update(float deltaTime);

		// access way for other systems to know where the sprite is
		float GetX() const { return pos.x; }
		float GetY() const { return pos.y; }

		AABB getAABB() noexcept;
		 
	private:
		 Sprite* wR_Sprite = nullptr;
		 vec2f pos{ 0.0f, 0.0f };

		 vec2f v{ 0.0f, 0.0f };

		 float wR_AnimeTimer = 0.0f;
		 static constexpr float wR_FrameTime = 0.1f; // seconds per frame
		 unsigned int wR_AnimeFrame = 0;

		//tick based fields
		 int tickCounter = 0;
		 static constexpr int ticksPerFrame = 7;

		// movement/animation state changer 
		enum state {idle = 0, right = 1, left = 2, up = 3, down = 4};
		state movement = idle;

		state prevMovement = idle;
	};
}
