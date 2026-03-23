#include <physics.hpp>
#include "../game.h"
#include <Level.hpp>
#include "../template.h"
#include <iostream>


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

	vec2f Physics::IntegratePosition(const vec2f& prevPos, const vec2f& v, float deltaTime) const
	{
		return prevPos + v * deltaTime;
	}

	void Physics::ResolvePlayerCollision(Player& player, const Level& level, float deltaTime, int activePhase)
	{
		vec2f pos = player.GetPos();
		vec2f v = player.GetVelocity();

		vec2f prevPos = pos;
		
		pos = player.IntegratePosition(prevPos, { v.x, 0.0f }, deltaTime);

		AABB prevBox = player.aabb + prevPos;
		AABB playerBox = player.GetAABB();
		
		

		

		for (const Collider& c : level.GetColliders())
		{
			bool isAny = (c.ps_type == phase_switch_lvl::any);
			bool isMatch = (static_cast<int>(c.ps_type) == activePhase);
			if (!(isAny || isMatch)) continue;

			auto result = playerBox.overlap(c.box);
			if (!result) continue;

			vec2f correction = *result;

			if (correction.x != 0.0f)
			{
				pos.x -= correction.x;
				v.x = 0.0f;

				playerBox = player.GetAABB();
			}
		}
		pos = player.IntegratePosition(pos, { 0.0f,v.y }, deltaTime);

		player.SetOnGround(false);
		playerBox = player.GetAABB();

		for (const Collider& c : level.GetColliders())
		{
			bool isAny = (c.ps_type == phase_switch_lvl::any);
			bool isMatch = (static_cast<int>(c.ps_type) == activePhase);
			if (!(isAny || isMatch)) continue;

			auto result = playerBox.overlap(c.box);
			if (!result) continue;

			vec2f correction = *result;

			if (c.type == ColliderType::OneWay)
			{
				if (v.y < 0.0f)
				{
					continue;
				}

				if (prevBox.max.y < c.box.min.y && playerBox.max.y > c.box.min.y)
				{
						pos.y -= correction.y;
						v.y = 0.0f;
						player.SetOnGround(true);
					
				}
					
			}
			else if (correction.y != 0.0f)
			{
				if (v.y >= 0.0f)
				{
					pos.y -= correction.y;
					v.y = 0.0f;
					player.SetOnGround(true);
				}
				else if (v.y < 0.0f) 
				{
					pos.y -= correction.y;
					v.y = 0.0f; 
				}
			}
		}

		player.SetPos(pos);
		player.SetVelocity(v);
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
			}
		}
	}
}
