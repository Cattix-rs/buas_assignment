#pragma once
#include "AABB.hpp"
#include "Level.hpp"
#include "SpriteSheet.hpp"
#include <memory>
#include "../surface.h"
#include "../template.h"

namespace Tmpl8
{
    class Player
    {
    public:
        Player() = default;
        // Initialize movement/animation system with the sprite and position pointers.
        void Init(Sprite* sprite, int px = 0, int py = 0);

        // Called each frame to handle input, movement and animation timing.
        void Update(float deltaTime);

        // access way for other systems to know where the sprite is
        float GetX() const { return pos.x; }
        float GetY() const { return pos.y; }

        vec2f GetPos() const { return pos; }
        vec2f GetVelocity() const { return v; }

        void SetPos(const vec2f& p) { pos = p; }
        void SetVelocity(const vec2f& vel) { v = vel; }

        void SetOnGround(bool value) { onGround = value; }
        bool IsOnGround() const { return onGround; }

        bool JumpedLastFrame() const { return jumpedLastFrame; }
        void SetJumpedLastFrame(bool s) { jumpedLastFrame = s; }

        vec2f IntegratePosition(float deltaTime);

        AABB GetAABB() const noexcept;

        void clampToScreen() noexcept;

        void Draw(Surface* screen);

        bool IsDead() const { return isDead; }

        void SetSizeFromSprite() noexcept;

        vec2f size() const noexcept;

        float GetEnergon() const noexcept { return energon; }
        void AddEnergon(float amount) noexcept { energon = std::min(maxEnergon, energon + amount); }

        int GetScore() const noexcept { return score; }
        void AddScore(uint32_t points) { score += points; }
        void Reset() { score = 0; energon = 100; isDead = false; }
        void debugShutdown() { energon -= maxEnergon; }
    private:
        float energon = 100.0f;          // current energon
        const float maxEnergon = 400.0f; // maximum energon
        float walkAccumulator = 0.0f;    // track distance walked to reduce energon per 10 pixels
        uint32_t score = 0;
        bool isDead = false;

        std::shared_ptr<Atlas::SpriteSheet> m_sheet;
        int m_legsFrame = 7;
        int m_TorsoFrame = 13;

        float Delta_x;

        Sprite* wR_Sprite = nullptr;
        vec2f pos{ 0.0f, 0.0f };
        float width = 0.0f;
        float height = 0.0f;

        vec2f v{ 0.0f, 0.0f };

        bool onGround = false;
        bool jumpedLastFrame = false;

        AABB aabb;

        float wR_AnimeTimer = 0.0f;
        static constexpr float wR_FrameTime = 150.0f; 
        unsigned int wR_AnimeFrame = 0;

        //tick based fields
        int tickCounter = 0;
        static constexpr int ticksPerFrame = 7;

        // movement/animation state changer 
        enum state { idle = 0, right = 1, left = 2, up = 3, down = 4 };
        state movement = idle;

        state prevMovement = idle;


    };
}
