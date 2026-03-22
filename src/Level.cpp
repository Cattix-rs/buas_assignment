#include <Level.hpp>

namespace Tmpl8
{

	namespace
	{
		Surface tiles("assets/pixelart-drawing_14.png");
		Sprite pickupSpriteNormal(new Surface("assets/energon_pickup_48x48.png"), 1);
		Sprite pickupSpriteBig(new Surface("assets/mineral_pickup_48x48.png"), 1);
	}




	const char Level_1[16][75] = {
		"cb cb cb cb cb cb cb cb cb cb cb cb cb cb cb cb cb cb cb cb cb cb cb cb cb",
		"cb ad bd cd ad bd cd ad bd cd ad bd cd ad bd cd bd cd ad bd ad bd cd ad cb",
		"cb ad bd cd ad bd cd ad bd cd ad bd cd ad bd cd bd cd ad bd ad bd cd ad cb",
		"cb ad bd cd ad bd cd ad bd cd ad bd cd ad bd cd bd cd ad bd ad bd cd ad cb",
		"cb ad bd cd ad bd cd ad bd cd ad bd cd ad bd cd bd cd ad bd ad bd cd ad cb",
		"cb ad bd cd ad bd cd ad bd cd ad bd cd ad bd cd bd cd ad bd ad bd cd ad cb",
		"cb ad bd cd ad bd cd ad bd cd ad bd cd ad bd cd bd cd ad bd ad bd cd ad cb",
		"cb ad bd cd ad bd cd ad bd cd ad bd cd ad bd cd bd cd ad bd ad bd cd ad cb",
		"cb ad bd cd ad bd cd ad bd cd ad bd cd ad bd cd bd cd ad bd ad bd cd ad cb",
		"cb ad bd cd ad bd cd ad bd cd ad bd cd ad bd cd bd cd ad bd ad bd cd ad cb",
		"cb ad bd cd ad bd cd ad bd cd ad bd cd ad bd cd bd cd ad bd ad bd cd ad cb",
		"cb ad bd cd ad bd cd ad bd cd ad bd cd ad bd cd bd cd ad bd ad bd cd ad cb",
		"cb ad bd cd ad bd cd ad bd cd ad bd cd ad bd cd bd cd ad bd ad bd cd ad cb",
		"cb ad bd cd ad bd cd ad bd cd ad bd cd ad bd cd bd cd ad bd ad bd cd ad cb",
		"cb cb bb ca ab bb ca ab bb ca ab bb ca ab bb ca ab bb ca ab bb ca bb cb cb",
		"bc bc bc bc bc bc bc bc bc bc bc bc bc bc bc bc bc bc bc bc bc bc bc bc bc"


	};

	const Collider colliders_1[] =
	{
		Collider{{0.0f, 200.0f},{400.0f,232.0f},ColliderType::OneWay,phase_switch_lvl::lvl_1Set1},
		Collider{{0.0f, 80.0f},{80.0f,123.0f},ColliderType::Solid,phase_switch_lvl::lvl_1Set1},
		Collider{{625.0f, 45.0f},{800.0f,65.0f},ColliderType::OneWay,phase_switch_lvl::lvl_1Set1},
		Collider{{580.0f, 290.0f},{800.0f,370.0f},ColliderType::Solid,phase_switch_lvl::lvl_1Set1},
		Collider{{0.0f, 0.0f},{800.0f,0.2f},ColliderType::Solid,phase_switch_lvl::any},
		Collider{{0.0f, 511.5f},{800.0f,512.0f},ColliderType::Floor,phase_switch_lvl::any}
	};

	const Pickup pickups_1[] =
	{
		Pickup{15.0f,40.0f, 48,phase_switch_lvl::lvl_1Set1,PickupType::big},
		Pickup{670.0f,0.0f, 48,phase_switch_lvl::lvl_1Set1,PickupType::normal},
		Pickup{600.0f,245.0f, 48,phase_switch_lvl::lvl_1Set1,PickupType::normal}
	};


	void DrawTile(int tx, int ty, Surface* screen, int x, int y)
	{
		Pixel* src = tiles.GetBuffer() + tx * 32 + (ty * 32) * 96;
		Pixel* dst = screen->GetBuffer() + x + y * 800;
		for (int i = 0; i < 32; i++)
			for (int j = 0; j < 32; j++)
			{
				// Check alpha threshold.
				unsigned char a = (src[j + i * 96] >> 24) & 0xFF;
				if (a > 128)
					dst[j + i * 800] = src[j + i * 96];

			}
	}


	void Level::AddCollider(const Collider& c)
	{
		assert(colliderCount < MaxColliders);
		
			colliders[colliderCount++] = c;
		
	}

	std::span< Pickup> Level::GetPickup()
	{
		return std::span<Pickup>(pickups.data(), pickupCount);
	}

	void Level::AddPickup(const Pickup& p)
	{
		if (pickupCount >= MaxPickups) return;

		pickups[pickupCount] = p;
		pickups[pickupCount].active = true;
		pickupCount++;
	}
	
/*	void Level::SwichPhase(int activePhase)
	{
		auto allPickups = GetPickup();

		
		for (auto& p : allPickups)
		{
			// 3. Logic check
			bool isAny = (p.ps_type == phase_switch_lvl::any);
			bool isMatch = (static_cast<int>(p.ps_type) == activePhase);

			if (isAny || isMatch)
			{
				p.active = true;  // <--- SET BREAKPOINT HERE
			}
			else
			{
				p.active = false;
			}
		}
	}*/

	void Level::RegeneratePickups(int activePhase)
	{
		
		for ( auto& p : GetPickup())
		{
			
			if (p.ps_type == phase_switch_lvl::any || static_cast<int>(p.ps_type) == activePhase)
			{
				p.active = true;
			}
		}
	}

	void Level::Init()
	{

		colliderCount = 0;
		pickupCount = 0;
		this->pickupSpriteNormal = &Tmpl8::pickupSpriteNormal;
		this->pickupSpriteBig = &Tmpl8::pickupSpriteBig;

		for (const Collider& c : colliders_1)
		{
			AddCollider(c);
		}

		for (const Pickup& p : pickups_1)
		{
			AddPickup(p);
		}
	}

	void Level::Draw(Surface* screen, int activePhase)
	{
		for (int y = 0; y < 16; y++)
			for (int x = 0; x < 25; x++)
			{
				int tx = Level_1[y][x * 3] - 'a';
				int ty = Level_1[y][x * 3 + 1] - 'a';
				DrawTile(tx, ty, screen, x * 32, y * 32);

			}

		for (int i = 0; i < pickupCount; i++)
		{
			auto& p = pickups[i];
			if (!pickups[i].active)continue;

			if(p.type == PickupType::big && pickupSpriteBig != nullptr)
			{
				pickupSpriteBig->Draw(screen, (int)p.pos.x, (int)p.pos.y);
			}
			else if (p.type == PickupType::normal && pickupSpriteNormal != nullptr)
			{
				pickupSpriteNormal->Draw(screen, (int)p.pos.x, (int)p.pos.y);
			}
		}

	}
	
	std::span<const Collider> Level::GetColliders() const
	{
		return std::span<const Collider>(colliders.data(), colliderCount);
	}
}
