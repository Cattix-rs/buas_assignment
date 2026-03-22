#pragma once
#include <array>
#include "../surface.h"
#include <span>

namespace Tmpl8
{
	enum class phase_swich_lvl
	{
		any,
		lvl_1Set1,
		lvl_1Set2,
		lvl_1set3
	};
	struct Pickup
	{
		vec2f pos;
		bool active = true;

		 int size = 48;
		 phase_swich_lvl ps_type = phase_swich_lvl::any;
		
		AABB GetAABB() const
		{
			return { pos, pos + vec2f(size,size) };
		}

		Pickup() = default;
		Pickup(float x, float y, int size, phase_swich_lvl ps_type) 
			: pos{x,y}
		, size{size}
		, ps_type{ps_type}
		{}
		
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
		phase_swich_lvl ps_type = phase_swich_lvl::any;
		ColliderType type = ColliderType::Solid;
		Collider() = default;
		Collider(vec2f min, vec2f max, ColliderType type, phase_swich_lvl ps_type) :box{ min,max }, type{type}, ps_type{ ps_type }
		{
			
		}
	};

	class Level
	{
	public:
		void Init();

		void Draw(Surface* screen);

		
		std::span<const Collider> GetColliders() const;
		int GetColliderCount() const { return colliderCount; }

		void AddCollider(const Collider& c);

		std::span< Pickup> GetPickup() ;
		int GetPickupCount() { return pickupCount; }

		void AddPickup(const Pickup& p);

	private:
		static constexpr int MaxColliders = 32;
		//AABB colliders[MaxColliders];
		std::array<Collider, MaxColliders> colliders{};
		int colliderCount = 3; // track how many are actually used
		static constexpr int MaxPickups = 32;
		std::array<Pickup, MaxPickups> pickups{};
		int pickupCount = 0; //track how many pickups are in use
	
	};
}
