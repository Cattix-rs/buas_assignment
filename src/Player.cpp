#include <Player.hpp>
#include <../surface.h>
#include <Level.hpp>
#include <physics.hpp>

//#include <cstdio>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace Tmpl8
{

    Physics u_physics;
    void Player::Init(Sprite* sprite, int px, int py)
    {
        wR_Sprite = sprite;
        pos.x = static_cast<float>(px);
        pos.y = static_cast<float>(py);

        // ensure stored size is taken from the sprite when available
        if (wR_Sprite)
        {
            width = static_cast<float>(wR_Sprite->GetWidth());
            height = static_cast<float>(wR_Sprite->GetHeight());
            wR_Sprite->SetFrame(0);
            aabb.min.x = 22.0f;
            aabb.max.x = width - 22.0f;
            aabb.min.y = 23.0f;
            aabb.max.y = height - 23.0f;
        }
        else
        {
            width = height = 0.0f;
        }



        wR_AnimeTimer = 100.0f;
        wR_AnimeFrame = 0;
        prevMovement = movement = state::idle;
        tickCounter = 0;

        u_physics.Init();
        v = vec2f{ 0.0f,0.0f };
    }



    float approach(float current, float target, float maxDelta)
    {
        float diff = target - current;
        if (diff > maxDelta) return current + maxDelta;
        if (diff < -maxDelta) return current - maxDelta;
        return target;
    }

    void Player::Update(float deltaTime)
    {
        if (!wR_Sprite) return;

        if (isDead) return;

        ///input: check for high bit meaning key is down
        bool left = (GetAsyncKeyState(VK_LEFT) & 0x8000) != 0;
        bool right = (GetAsyncKeyState(VK_RIGHT) & 0x8000) != 0;
        bool jump = (GetAsyncKeyState(VK_SPACE) & 0x8000) != 0;

        const float jumpStrength = -0.35f; // tuned for ms system 325 good
        const float speed_x = 0.2f;
        // units per second
        float deceleration = 0.0003666f;   // how fast we slow down

        if (left)
        {
            v.x = -speed_x;
        }
        else if (right)
        {
            v.x = speed_x;
        }
        else
        {
            v.x = approach(v.x, 0.0f, deceleration * deltaTime);
        }

        bool jumpPressed = jump && !jumpedLastFrame;
        jumpedLastFrame = jump;

        if (left) v.x = -speed_x;
        if (right) v.x = speed_x;

        u_physics.Applyg(v, deltaTime);

        bool isWalking = std::abs(v.x) > 0.01f;

        if (v.x == 0.0f)   walkAccumulator = 0.0f;

        if (isWalking)
        {
            float distanceMoved = v.x * deltaTime;
            walkAccumulator += distanceMoved;

            const float pixelsPerEnergon = 10.0f;
            while (walkAccumulator >= pixelsPerEnergon)
            {
                if (energon > 0.0f) energon -= 0.00015f * deltaTime; 
                walkAccumulator -= pixelsPerEnergon;
            }
        }

        if (jumpPressed && onGround)
        {
            if (energon >= 0.01f)
            {
                pos.y -= 0.1f;
                v.y = jumpStrength;
                onGround = false;
                energon -= 0.1f; 
            }
        }

        state newState = state::idle;
        if (right) newState = state::right;
        else if (left) newState = state::left;



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
            wR_AnimeTimer += deltaTime; // add elapsed seconds

            while (wR_AnimeTimer >= wR_FrameTime) // seconds per frame
            {
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


    vec2f Player::IntegratePosition(float deltaTime)
    {
        pos += v * deltaTime;
        return pos;
    }

    AABB Player::GetAABB() const noexcept
    {
        return aabb + pos;
    }

    void Player::clampToScreen() noexcept
    {
        AABB box = GetAABB();

        if (box.min.x < 0.0f)
        {
            // move sprite right so box.min.x == 0
            pos.x = -aabb.min.x;
            v.x = 0.0f;
        }

        if (box.max.x >= ScreenWidth)
        {
            // move sprite left so box.max.x == ScreenWidth - 1
            pos.x = ScreenWidth - aabb.max.x;
            v.x = 0.0f;
        }

        if (box.min.y < 0.0f)
        {
            pos.y = -aabb.min.y;
        }

        if (box.max.y >= ScreenHeight)
        {
            pos.y = ScreenHeight - aabb.max.y;
            v.y = 0.0f;
            onGround = true;
        }

        if (energon <= 0.0f)
        {
            isDead = true;
        }
    }



    void Player::Draw(Surface* screen)//needs to be be in game or ui class
    {
        int barWidth = static_cast<int>((GetEnergon() / 100.0f) * 100);
        int barHeight = 10;
        int barX = 10;
        int barY = 10;

        

       
        screen->Box(barX + barWidth, barY, barX + 200, barY + barHeight, 0x333333);
        if (!isDead)
        {
            screen->Bar(barX, barY, barX + barWidth, barY + barHeight, 0x0000FF); // solid blue
        }


        if (isDead)
        {
            const char* msg = "YOU LOST";

            int msgX = 800 / 2 - 50;
            int msgY = 512 / 2 - 10;
            screen->Print(msg, msgX, msgY, 0xFF0000);

        }
    }

    void Player::SetSizeFromSprite() noexcept
    {
        if (wR_Sprite)
        {
            width = static_cast<float>(wR_Sprite->GetWidth());
            height = static_cast<float>(wR_Sprite->GetHeight());
        }
    }

    vec2f Player::size() const noexcept
    {
        if (!wR_Sprite) return vec2f{ 0.0f, 0.0f };
        return vec2f{ static_cast<float>(wR_Sprite->GetWidth()), static_cast<float>(wR_Sprite->GetHeight()) };
    }


}
