

#include "inc/Movement_animations.hpp"
#include <windows.h>

namespace Tmpl8
{
	//namespace movement_walkR
	//{
		static Sprite* wR_Sprite = nullptr;
		static int* wR_px = nullptr;
		static int* wR_py = nullptr;

		static float wR_AnimeTimer = 0.0f;
		static const float wR_FrameTime = 0.1f; // seconds per frame
		static unsigned int wR_AnimeFrame = 0;

		void Init(Sprite* sprite, int* px, int* py)
		{
			wR_Sprite = sprite;
			wR_px = px;
			wR_py = py;
			wR_AnimeTimer = 0.0f;
			wR_AnimeFrame = 0;
			if (wR_Sprite) wR_Sprite->SetFrame(0);
		}

			void Update(float deltaTime)
		{
			if (!wR_Sprite || !wR_px || !wR_py) return;

			///input: check for high bit meaning key is down
			bool left = (GetAsyncKeyState(VK_LEFT) & 0x8000) != 0;
			bool right = (GetAsyncKeyState(VK_RIGHT) & 0x8000) != 0;
			bool up = (GetAsyncKeyState(VK_UP) & 0x8000) != 0;
			bool down = (GetAsyncKeyState(VK_DOWN) & 0x8000) != 0;

			if (left) (*wR_px) -= 1;
			if (right) (*wR_px) += 2;
			if (up) (*wR_py) -= 1;
			if (down)  (*wR_py) += 1;

			//animetion advance when moveing right.
			if (right)
			{
				wR_AnimeTimer += deltaTime;
				while (wR_AnimeTimer >= wR_FrameTime)
				{
					wR_AnimeTimer -= wR_FrameTime;
					wR_AnimeFrame = (wR_AnimeFrame + 1) % wR_Sprite->Frames();
					wR_Sprite->SetFrame(wR_AnimeFrame);
				}
			}
			else
			{
				wR_AnimeTimer = 0.0f;
				wR_AnimeFrame = 0;
				wR_Sprite->SetFrame(0);

			}
			
				
			
			
		}




















	//}
}
