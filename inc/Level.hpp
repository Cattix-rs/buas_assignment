#pragma once

#include "../surface.h"

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
		ColliderType type;
	};

	class Level
	{
	public:
		void Init();

		void Draw(Surface* screen);

		
		const AABB* GetColliders() const { return colliders; }
		int GetColliderCount() const { return colliderCount; }

	private:
		static constexpr int MaxColliders = 32;
		AABB colliders[MaxColliders];
		int colliderCount = 0; // track how many are actually used
	
	};
}
