#include <Player.hpp>
#include <../surface.h>
#include <Level.hpp>
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
        pos.y = static_cast<float>(py);

        // ensure stored size is taken from the sprite when available
        if (wR_Sprite)
        {
            width = static_cast<float>(wR_Sprite->GetWidth());
            height = static_cast<float>(wR_Sprite->GetHeight());
            wR_Sprite->SetFrame(0);
            aabb.min.x = 22.0f;
            aabb.max.x = width - 22.0f;
            aabb.min.y = 19.0f;
            aabb.max.y = height - 19.0f;
        }
        else
        {
            width = height = 0.0f;
        }



        wR_AnimeTimer = 0.0f;
        wR_AnimeFrame = 0;
        prevMovement = movement = state::idle;
        tickCounter = 0;

        u_physics.Init();
        v = vec2f{ 0.0f,0.0f };
    }



    void Player::Update(float deltaTime)
    {
        if (!wR_Sprite) return;

        auto approach = [](float current, float target, float maxDelta)
            {
                float diff = target - current;
                if (diff > maxDelta) return current + maxDelta;
                if (diff < -maxDelta) return current - maxDelta;
                return target;
            };

        ///input: check for high bit meaning key is down
        bool left = (GetAsyncKeyState(VK_LEFT) & 0x8000) != 0;
        bool right = (GetAsyncKeyState(VK_RIGHT) & 0x8000) != 0;
        bool up = (GetAsyncKeyState(VK_UP) & 0x8000) != 0;
        bool down = (GetAsyncKeyState(VK_DOWN) & 0x8000) != 0;

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



        if (left) v.x = -speed_x;
        if (right) v.x = speed_x;
        if (up) v.y = -0.1f;
        if (down)  v.y = 0.1f;

       
        pos = u_physics.IntegratePosition(pos, v, deltaTime);

        vec2f nextPos = pos + v * deltaTime;
        AABB nextBox = aabb + nextPos;

        if (level)
        {
            AABB playerBox = getAABB();

            for (const Collider& c : level->GetColliders())
            {
                auto result = playerBox.overlap(c.box);

                if (!result)
                    continue;

                vec2f correction = *result;

                if (c.type == ColliderType::OneWay)
                {
                    if (v.y < 0) continue;
                    if (correction.y <= 0) continue;
                }

               /* pos += correction;

                if (correction.y < 0)
                    v.y = 0;*/
                if (correction.x != 0.0f)
                {
	                nextPos.x += correction.x; v.x = 0;
                    v.x = 0.0f;
                }
                if (correction.y != 0.0f)
                {
	                nextPos.y += correction.y; v.y = 0.0f;
                    v.y = 0.0f;
                }
            }
        }
        u_physics.Applyg(v, deltaTime);
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

        float newX = pos.x + v.x;
        float newY = pos.y + v.y;

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
        clampToScreen();
    }

    

    AABB Player::getAABB() const noexcept
    {
        return aabb + pos;
    }

    

    void Player::clampToScreen() noexcept
    {
        AABB box = getAABB();

        if (box.min.x < 0.0f)
        {
            // move sprite right so box.min.x == 0
            pos.x = -aabb.min.x;
            v.x = 0.0f;
        }

        if (box.max.x >= ScreenWidth)
        {
            // move sprite left so box.max.x == ScreenWidth - 1
            pos.x = ScreenWidth - aabb.max.x - 1;
            v.x = 0.0f;
        }

        if (box.min.y < 0.0f)
        {
            pos.y = -aabb.min.y;
        }

        if (box.max.y >= ScreenHeight)
        {
            pos.y = ScreenHeight - aabb.max.y - 1;
            v.y = 0.0f;
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
