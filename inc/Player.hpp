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

		vec2f GetPos() const { return pos; }
		vec2f GetVelocity() const { return v; }

		void SetPos(const vec2f& p) { pos = p; }
		void SetVelocity(const vec2f& vel) { v = vel; }
		
		void SetOnGround(bool value) { onGround = value; }
		bool IsOnGround() const { return onGround; }

		bool JumpedLastFrame() const { return jumpedLastFrame; }
		void SetJumpedLastFrame(bool s) { jumpedLastFrame = s; }

		vec2f IntegratePosition(const vec2f& pos, const vec2f& v, float deltaTime) const;

		AABB aabb;

		AABB GetAABB() const noexcept;

		AABB PlayerBox = GetAABB();
		 
		void clampToScreen() noexcept;

		void Draw(Surface* screen);
		
		bool isDead = false;
		bool IsDead() const { return isDead; }
		
		void SetSizeFromSprite() noexcept;
			
		vec2f size() const noexcept;

		float GetEnergon() const noexcept { return energon; }
		void AddEnergon(float amount) noexcept { energon = std::min(maxEnergon, energon + amount); }
	private:
		float energon = 100.0f;          // current energon
		const float maxEnergon = 400.0f; // maximum energon
		float walkAccumulator = 0.0f;    // track distance walked to reduce energon per 10 pixels

		float Delta_x;
		


		 Sprite* wR_Sprite = nullptr;
		 vec2f pos{ 0.0f, 0.0f };
		 float width = 0.0f;
		 float height = 0.0f;

		 vec2f v{ 0.0f, 0.0f };
		 vec2f prevPos;

		 bool onGround = false;
		 bool jumpedLastFrame = false;

		 

		

		 float wR_AnimeTimer = 0.0f;
		 static constexpr float wR_FrameTime = 60.5f; // seconds per frame
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
	