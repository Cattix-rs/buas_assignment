#include <Level.hpp>
#include <physics.hpp>
#include <Player.hpp>
#include "../template.h"
// this File Includes AI generated code AI1
namespace Tmpl8
{
    void Physics::Init()
    {
        g = vec2f{ 0.0f, 0.0002333f };
    }

    void Physics::Applyg(vec2f& v, float deltaTime) const
    {
        v.y += g.y * deltaTime;
    }

    void Physics::ResolvePlayerCollision(Player& player, const Level& level, float deltaTime, int activePhase)
    {
        AABB prevAABB = player.GetAABB();

        vec2f pos = player.IntegratePosition(deltaTime);
        vec2f v = player.GetVelocity();

        AABB playerBox = player.GetAABB();

        player.SetOnGround(false);

        for (const Collider& c : level.GetColliders())
        {
            bool isAny = (c.ps_type == phase_switch_lvl::any);
            bool isMatch = (static_cast<int>(c.ps_type) == activePhase);
            if (!(isAny || isMatch)) continue;

            if (auto result = playerBox.overlap(c.box))
            {
                // If the velocity is pointing away from the collision normal, skip resolution to prevent sticking.
                if (v.dot(*result) < 0.0f) continue;

                if (c.type == ColliderType::OneWay)
                {
                    if (v.y > 0.0f && prevAABB.max.y <= c.box.min.y)
                    {
                        pos.y -= result->y; // Resolve collision.
                        pos.y = std::round(pos.y); 
                        v.y = 0.0f;
                        player.SetOnGround(true);
                    }
                }
                else
                {
                    pos -= *result; // Resolve collision.
                    if (abs(result->x) > 0.0f)
                    {
                        v.x = 0.0f;
                    }
                    else
                    {
                        if (v.y > 0.0f && result->y > 0.0f)
                        {
                            pos.y = std::round(pos.y); // Snap to pixel grid to prevent jittering
                            player.SetOnGround(true);
                        }
                        v.y = 0.0f;
                    }
                }
            }
        }

        player.SetPos(pos);
        player.SetVelocity(v);

        player.clampToScreen();
    }

    void Physics::CheckPickupCollision(Player& player, Level& level)
    {
        AABB playerBox = player.GetAABB();

        for (auto& pickup : level.GetPickup())
        {
            if (!pickup.active) continue;

            AABB pickupBox = pickup.GetAABB();

            if (playerBox.overlap(pickupBox))
            {
                pickup.active = false;
                player.AddEnergon(pickup.pickup_Value);
                player.AddScore(2 * pickup.pickup_Value);
            }
        }
    }
}
