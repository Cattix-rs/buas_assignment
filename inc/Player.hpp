#pragma once
#include "AABB.hpp"
#include "Level.hpp"
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

		void SetLevel(Level* level) { this->level = level; }

		AABB getAABB() const noexcept;

		AABB PlayerBox = getAABB();
		 
		void clampToScreen() noexcept;
		
		
		void SetSizeFromSprite() noexcept;
			
		vec2f size() const noexcept;
	private:
		 Sprite* wR_Sprite = nullptr;
		 vec2f pos{ 0.0f, 0.0f };
		 float width = 0.0f;
		 float height = 0.0f;

		 vec2f v{ 0.0f, 0.0f };
		 vec2f prevPos;

		 bool onGround = false;
		 bool jumpPressedLastFrame = false;

		 Level* level = nullptr;

		 AABB aabb;

		 float wR_AnimeTimer = 0.0f;
		 static constexpr float wR_FrameTime = 45.5f; // seconds per frame
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
	