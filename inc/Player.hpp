#pragma once
#include "../surface.h"

namespace Tmpl8
{
	class Player
	{
	public:
		Player() = default;
		// Initialize movement/animation system with the sprite and position pointers.
		void Init(Sprite* sprite, int* px, int* py);

		// Called each frame to handle input, movement and animation timing.
		void Update(float deltaTime);
	private:
		 Sprite* wR_Sprite = nullptr;
		 int* wR_px = nullptr;
		 int* wR_py = nullptr;

		 float wR_AnimeTimer = 0.0f;
		 static constexpr float wR_FrameTime = 0.1f; // seconds per frame
		 unsigned int wR_AnimeFrame = 0;

		//tick baseed fields
		 int tickCounter = 0;
		 static constexpr int ticksPerFrame = 7;
	};
}
