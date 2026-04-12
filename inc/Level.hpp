#pragma once
#include <array>
#include "../surface.h"
#include <span>

namespace Tmpl8
{
	enum class phase_switch_lvl
	{
		any,
		lvl_1Set1,
		lvl_1Set2,
		lvl_1Set3,
		lvl_2set1 // not implemented 
	};
	
	enum class PickupType
	{
		normal,
		big
	};
	struct Pickup
	{
		vec2f pos;
		bool active = true;
		PickupType type = PickupType::normal;
		int size = 48;
		phase_switch_lvl ps_type = phase_switch_lvl::any;
		float pickup_Value;
		
		AABB GetAABB() const
		{
			return { pos, pos + vec2f(size,size) };
		}

		Pickup() = default;
		Pickup(float x, float y, int size, phase_switch_lvl ps_type,PickupType type) 
			: pos{x,y}
		, size{size}
		, ps_type{ps_type}
		, type{type}
		{
			if (type == PickupType::big)
			{
				pickup_Value = 30.0f;
			}
			else
			{
				pickup_Value = 10.0f;
			}
		}
		
	};

	enum class ColliderType
	{
		Floor,
		Solid,
		OneWay
	};

	struct Collider
	{
		
		AABB box;
		phase_switch_lvl ps_type = phase_switch_lvl::any;
		ColliderType type = ColliderType::Solid;
		Collider() = default;
		Collider(vec2f min, vec2f max, ColliderType type, phase_switch_lvl ps_type) :box{ min,max }, type{type}, ps_type{ ps_type }
		{
			
		}
	};

	struct PhaseTileMap
	{
		const char (*data)[75];
		phase_switch_lvl phase;
	};

	class Level
	{
	public:
		void Init();

		void Draw(Surface* screen, int activePhase);

		
		std::span<const Collider> GetColliders() const;
		int GetColliderCount() const { return colliderCount; }

		void AddCollider(const Collider& c);

		std::span< Pickup> GetPickup() ;
		int GetPickupCount() { return pickupCount; }

		void AddPickup(const Pickup& p);
		float pickup_Value;
		void SwichPhase(int activePhase);
		void RegeneratePickups(int activePhase);
	private:
		static constexpr int MaxColliders = 32;
		//AABB colliders[MaxColliders];
		std::array<Collider, MaxColliders> colliders{};
		int colliderCount = 0; // track how many are actually used
		static constexpr int MaxPickups = 32;
		std::array<Pickup, MaxPickups> pickups{};
		int pickupCount = 0; //track how many pickups are in use
		Sprite* pickupSpriteNormal = nullptr;
		Sprite* pickupSpriteBig = nullptr;
		
	
	};
}
