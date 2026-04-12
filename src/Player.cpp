#include <Player.hpp>
#include <Input.hpp>
#include <physics.hpp>
#include <resourceManager.hpp>

#include <../surface.h>

//#include <cstdio>

namespace Tmpl8
{
    Physics u_physics;

    void Player::Init(int px, int py)
    {
       
        pos.x = static_cast<float>(px);
        pos.y = static_cast<float>(py);

        m_sheet = Atlas::ResourceManager::loadSpriteSheetFromTxt(
            "assets/sprites.txt",
            "assets/optimus.png",
            Atlas::BlendMode::AlphaBlend
        );

        // ensure stored size is taken from the sprite when available
        if (m_sheet)
        {
            m_Sprite = &m_sheet->getSprite(14);
            m_TorsoSprite = &m_sheet->getSprite(10);

            // Now that m_Sprite is set, we can get width/height
            width = static_cast<float>(m_Sprite->GetWidth());
            height = static_cast<float>(m_Sprite->GetHeight());

            aabb.min.x = 0.0f;
            aabb.max.x = width + 16.0f;
            aabb.min.y = -20.0f;
            aabb.max.y = height + 0.0f;
        }
        else
        {
            width = height = 0.0f;
        }

        m_AnimeTimer = 100.0f;
        m_AnimeFrame = 0;
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
        if (!m_Sprite) return;

        if (isDead) return;

        const int walkSequence[4] = {14,21,20,13};
        const int torsoSequene[4] = {10,6,7,11};

        const float jumpStrength = -0.35f; // tuned for ms system 325 good
        const float speed_x = 0.2f;
        // units per second
        float deceleration = 0.0003666f;   // how fast we slow down

        if (Input::IsDown(SDL_SCANCODE_LEFT)) 
        {
            v.x = -speed_x;
            movement = state::left;
        }
        else if (Input::IsDown(SDL_SCANCODE_RIGHT))
        {
            v.x = speed_x;
            movement = state::right;
        }
        else
        {
            v.x = approach(v.x, 0.0f, deceleration * deltaTime);
            movement = state::idle;
        }

        bool jumpPressed = Input::IsPressed(SDL_SCANCODE_SPACE) && !jumpedLastFrame;
        jumpedLastFrame = Input::IsPressed(SDL_SCANCODE_SPACE);

        u_physics.Applyg(v, deltaTime);

        bool isWalking = std::abs(v.x) > 0.01f;

        if (v.x == 0.0f)   walkAccumulator = 0.0f;

        if (isWalking)
        {
            float distanceMoved = std::abs(v.x) * deltaTime;
            walkAccumulator += distanceMoved;

            const float pixelsPerEnergon = 10.0f;
            while (walkAccumulator >= pixelsPerEnergon)
            {
                if (energon > 0.0f) energon -= 0.02f * deltaTime;
                walkAccumulator -= pixelsPerEnergon;
            }
        }

        if (jumpPressed && onGround)
        {
            if (energon >= 0.1f)
            {
                pos.y -= 0.02f;
                 v.y = jumpStrength;
                onGround = false;
                energon -= 5.0f;
            }
        }

        state newState = state::idle;
        if (v.x > 0.01f) 
            newState = state::right;

        else if (v.x < -0.01f) 
            newState = state::left;



        movement = newState;

        if (movement != prevMovement)
        {
            tickCounter = 0;
            m_AnimeFrame = 0;
            prevMovement = movement;
        }



        //animation advance when moving right. tick based animation

        switch (movement)
        {
        case state::right:
        {
            m_AnimeTimer += deltaTime; // add elapsed seconds

            while (m_AnimeTimer >= m_FrameTime) // seconds per frame
            {
                m_AnimeTimer -= m_FrameTime;
                m_AnimeFrame = (m_AnimeFrame + 1) % 4;

                int actualFrame = walkSequence[m_AnimeFrame];
                int actualFrame_T = torsoSequene[m_AnimeFrame];

                if (m_sheet)
                {
                    m_Sprite = &m_sheet->getSprite(actualFrame);
                    m_TorsoSprite = &m_sheet->getSprite(actualFrame_T);
                }
            }
            break;
        }
        case state::left:
        {
            m_AnimeTimer += deltaTime;
            while (m_AnimeTimer >= m_FrameTime)
            {
                m_AnimeTimer -= m_FrameTime;
                m_AnimeFrame = (m_AnimeFrame + 1) % 4;

                int actualFrame = walkSequence[m_AnimeFrame];
                int actualFrame_T = torsoSequene[m_AnimeFrame];

                if (m_sheet)
                {
                    m_Sprite = &m_sheet->getSprite(actualFrame);
                    m_TorsoSprite = &m_sheet->getSprite(actualFrame_T);
                }
            } 
            break;
        }
        case state::up:
        case state::down:
        default:
            //reset when no movement
            tickCounter = 0;
            m_AnimeFrame = 0;
       

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



    void Player::Draw(Surface* screen)
    {
        int barWidth = static_cast<int>((GetEnergon() / 100.0f) * 100);
        int barHeight = 10;
        int barX = 10;
        int barY = 10;
        if (m_Sprite)
        {
            m_Sprite->Draw(pos, screen, v.x < 0.01f);
        }
     
        if (m_TorsoSprite)
        {
            vec2f TorsoPos = {pos.x, pos.y - m_Sprite->GetHeight() + 15.0f};
            m_TorsoSprite->Draw(TorsoPos, screen, v.x < 0.01f);
        }


       
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
        if (m_Sprite)
        {
            width = static_cast<float>(m_Sprite->GetWidth());
            height = static_cast<float>(m_Sprite->GetHeight());
        }
    }

    vec2f Player::size() const noexcept
    {
        if (!m_Sprite) return vec2f{ 0.0f, 0.0f };
        return vec2f{ static_cast<float>(m_Sprite->GetWidth()), static_cast<float>(m_Sprite->GetHeight()) };
    }


}
