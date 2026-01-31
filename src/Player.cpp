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
        }

        void Player::Update(float deltaTime)
        {
            if (!wR_Sprite) return;

            ///input: check for high bit meaning key is down
            bool left = (GetAsyncKeyState(VK_LEFT) & 0x8000) != 0;
            bool right = (GetAsyncKeyState(VK_RIGHT) & 0x8000) != 0;
            bool up = (GetAsyncKeyState(VK_UP) & 0x8000) != 0;
            bool down = (GetAsyncKeyState(VK_DOWN) & 0x8000) != 0;
            

            if (left) (wR_px) -= x_speed ;
            if (right) (wR_px) += x_speed;
            if (up) (wR_py) -= y_speed;
            if (down)  (wR_py) += y_speed;

            //animetion advance when moveing right. tichk based animation
            if (right)
            {
                tickCounter++;
                if (tickCounter >= ticksPerFrame)
                {
                    tickCounter = 0;
                    wR_AnimeTimer -= wR_FrameTime;
                    wR_AnimeFrame = (wR_AnimeFrame + 1) % wR_Sprite->Frames();
                    wR_Sprite->SetFrame(wR_AnimeFrame);
                }
                

                //wR_AnimeTimer += deltaTime;

               

                //while (wR_AnimeTimer >= wR_FrameTime)
                //{
                //    wR_AnimeTimer -= wR_FrameTime;
                //    wR_AnimeFrame = (wR_AnimeFrame + 1) % wR_Sprite->Frames();
                //    wR_Sprite->SetFrame(wR_AnimeFrame);
                //}
            }
            else
            {
                //reset when no movment
                tickCounter = 0;
                wR_AnimeFrame = 0;
                wR_Sprite->SetFrame(0);

            }
        }
    
}
