#pragma once
#include <array>
#include "../surface.h"
#include <span>

namespace Tmpl8
{

	enum class ColliderType
	{
		Solid,
		OneWay
	};

	struct Collider
	{
		AABB box;
		ColliderType type = ColliderType::Solid;
		Collider() = default;
		Collider(vec2f min, vec2f max, ColliderType type) :box{ min,max }, type{type}
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

	private:
		static constexpr int MaxColliders = 32;
		//AABB colliders[MaxColliders];
		std::array<Collider, MaxColliders> colliders{};
		int colliderCount = 0; // track how many are actually used
	
	};
}
