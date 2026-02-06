#include <Player.hpp>
//#include <cstdio>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace Tmpl8
{
        void Player::Init(Sprite* sprite, int px, int py)
        {
            wR_Sprite = sprite;
            wR_px = px;
            wR_py = py;
            wR_AnimeTimer = 0.0f;
            wR_AnimeFrame = 0;
            if (wR_Sprite) wR_Sprite->SetFrame(0);
            prevMovement = movement = state::idle;
            tickCounter = 0;
        }


        void Player::Update(float deltaTime)
        {
            if (!wR_Sprite) return;

            ///input: check for high bit meaning key is down
            bool left = (GetAsyncKeyState(VK_LEFT) & 0x8000) != 0;
            bool right = (GetAsyncKeyState(VK_RIGHT) & 0x8000) != 0;
            bool up = (GetAsyncKeyState(VK_UP) & 0x8000) != 0;
            bool down = (GetAsyncKeyState(VK_DOWN) & 0x8000) != 0;
            

            if (left) (wR_px) -= x_speed;
            if (right) (wR_px) += x_speed;
            if (up) (wR_py) -= y_speed;
            if (down)  (wR_py) += y_speed;

            state newState = state::idle;
            if (right) newState = state::right;
            else if (left) newState = state::left;
            else if (up) newState = state::up;
            else if (down) newState = state::down;

            movement = newState;

            if (movement != prevMovement)
            {
                tickCounter = 0;
                wR_AnimeFrame = 0;
                if (wR_Sprite) wR_Sprite->SetFrame(0);
                prevMovement = movement;
            }

            //animation advance when moving right. tick based animation
            switch (movement)
            {
	            case state::right:
	            {
	                tickCounter++;
	                if (tickCounter >= ticksPerFrame)
	                {
	                    tickCounter = 0;
	                    wR_AnimeTimer -= wR_FrameTime;
	                    wR_AnimeFrame = (wR_AnimeFrame + 1) % wR_Sprite->Frames();
	                    wR_Sprite->SetFrame(wR_AnimeFrame);
	                }
	                break;
	            }
            case state::left:
            case state::up:
            case state::down:
            	default:
                //reset when no movement
                tickCounter = 0;
                wR_AnimeFrame = 0;
                wR_Sprite->SetFrame(0);

            }
        }
    
}
