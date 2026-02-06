#pragma once
#include "../surface.h"

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
		int GetX() const { return wR_px; }
		int GetY() const { return wR_py; }

		// y and x speed definition place holder for wehn v repleces this 
		int x_speed = 2;
		int y_speed = 1;
		
		// current sprite def
		 
	private:
		 Sprite* wR_Sprite = nullptr;
		 int wR_px = 0;
		 int wR_py = 0;

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
