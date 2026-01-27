#pragma once
#include "../surface.h"

namespace Tmpl8
{
	namespace Movement
	{
		// Initialize movement/animation system with the sprite and position pointers.
		void Init(Sprite* sprite, int* px, int* py);

		

		// Called each frame to handle input, movement and animation timing.
		void Update(float deltaTime);
	}
}
