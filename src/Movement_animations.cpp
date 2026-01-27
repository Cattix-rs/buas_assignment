#include <Movement_animations.hpp>
//#include <cstdio>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace Tmpl8
{
     
    
        

        void Movement::Init(Sprite* sprite, int* px, int* py)
        {
            wR_Sprite = sprite;
            wR_px = px;
            wR_py = py;
            wR_AnimeTimer = 0.0f;
            wR_AnimeFrame = 0;
            if (wR_Sprite) wR_Sprite->SetFrame(0);
        }

        void Movement::Update(float deltaTime)
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
