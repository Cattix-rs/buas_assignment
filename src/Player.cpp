#include <Player.hpp>
#include <../surface.h>
#include <physics.hpp>
//#include <cstdio>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace Tmpl8
{
    static physics u_physics;
        void Player::Init(Sprite* sprite, int px, int py)
        {
            wR_Sprite = sprite;
            pos.x = static_cast<float>(px);
            pos.y =static_cast<float>(py);
            
            wR_AnimeTimer = 0.0f;
            wR_AnimeFrame = 0;
            if (wR_Sprite) wR_Sprite->SetFrame(0);
            prevMovement = movement = state::idle;
            tickCounter = 0;

            u_physics.Init();
            v = vec2f{ 0.0f,0.0f };
        }

        

        void Player::Update(float deltaTime)
        {
            if (!wR_Sprite) return;

            ///input: check for high bit meaning key is down
            bool left = (GetAsyncKeyState(VK_LEFT) & 0x8000) != 0;
            bool right = (GetAsyncKeyState(VK_RIGHT) & 0x8000) != 0;
            bool up = (GetAsyncKeyState(VK_UP) & 0x8000) != 0;
            bool down = (GetAsyncKeyState(VK_DOWN) & 0x8000) != 0;
            

            if (left) v.x -= 0.02f;
            if (right) v.x += 0.02f;
            if (up) v.y -= 0.01f;
            if (down)  v.y +=0.01f;

            u_physics.Applyg(v, deltaTime);
            pos = u_physics.IntegratePosition(pos, v, deltaTime);

             AABB box - getAABB();

            if (box.min.x <0.0f)
            {
                pos.x -= box.min.x;
            }

            if (box.max.x > ScreenWidth)
            {
                pos.x -= (box.max.x - ScreenWidth);
            }

            if (box.min.y < 0.0f)
            {
                pos.y -= box.min.y;
            }

            if (box.max.y > ScreenHeight)
            {
                pos.y -= (box.max.y - ScreenHeight);
                v.y = 0.0f;
            }


            clampToScreen();

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

        vec2f size()
        {
            static_cast<float>(theSprite.GetWidth()),
                static_cast<float>(theSprite.GetHeight())
        };

        AABB Player::getAABB() noexcept
        {
            return AABB
            {
            pos,
            pos + size
            };
        }
}
