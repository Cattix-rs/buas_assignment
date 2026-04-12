#include <Level.hpp>

namespace Tmpl8
{

	namespace
	{
		Surface tiles("assets/Blocks_n_Bushes_v3.png");
		Sprite pickupSpriteNormal(new Surface("assets/energon_pickup_48x48.png"), 1);
		Sprite pickupSpriteBig(new Surface("assets/mineral_pickup_48x48.png"), 1);
	}




	const char Level_1[16][75] = 
	{
		"cb cb cb cb cb cb cb cb cb cb cb cb cb cb cb cb cb cb cb cb cb cb cb cb cb",
		"cb ad bd cd ad bd cd ad bd cd ad bd cd ad bd cd bd cd ad bd ad bd cd ad cb",
		"cb ad bd cd ad bd cd ad bd cd ad bd cd ad bd cd bd cd ad bd ad bd cd ad cb",
		"cb ad bd cd ad bd cd ad bd cd ad bd cd ad bd cd bd cd ad bd ad bd cd ad cb",
		"cb ad bd cd ad bd cd ad bd cd ad bd cd ad bd cd bd cd ad bd ad bd cd ad cb",
		"cb ad bd cd ad bd cd ad bd cd ad bd cd ad bd cd bd cd ad bd ad bd cd ad cb",
		"cb ad bd cd ad bd cd ad bd cd ad bd cd ad bd cd bd cd ad bd ad bd cd ad cb",
		"cb ad bd cd ad bd cd ab ad ab ad bd cd ad bd cd bd cd ad bd ad bd cd ad cb",
		"cb ad bd cd ad bd cd ad bd cd ad bd cd ad bd cd bd cd ad bd ad bd cd ad cb",
		"cb ad bd cd ad bd cd ad bd cd ad bd cd ad bd cd bd cd ad bd ad bd cd ad cb",
		"cb ad bd cd ad bd cd ad bd cd ad bd cd ad bd cd bd cd ad bd ad bd cd ad cb",
		"cb ad bd cd ad bd cd ad bd cd ad bd cd ad bd cd bd cd ad bd ad bd cd ad cb",
		"cb ad bd cd ad bd cd ad bd cd ad bd cd ad bd cd bd cd ad bd ad bd cd ad cb",
		"cb ad bd cd ad bd cd ad bd cd ad bd cd ad bd cd bd cd ad bd ad bd cd ad cb",
		"cb cb bb ca ab bb ca ab bb ca ab bb ca ab bb ca ab bb ca ab bb ca bb cb cb",
		"bc bc bc bc bc bc bc bc bc bc bc bc bc bc bc bc bc bc bc bc bc bc bc bc bc"
	};

	const char Level_1_Set1[16][75] = 
	{
		"zb zb zb zb zb zb zb zb zb zb zb zb zb zb zb zb zb zb zb zb zb zb zb zb zb",
		"zb zd zd zd zd zd zd zd zd zb zd zd zd zd zd zd zd zd zd zd zd zd zd zd zb",
		"hb hb zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd ha ha ha ha",
		"zb zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zb",
		"zb zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zb",
		"zb zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zb",
		"zb zd zd zd zd zd zd zd zd zd zd zz zd zd zd zd zd zd zd zd zd zd zd zd zb",
		"zd za zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zb",
		"ha ha ha ha ha ha ha ha ha ha ha ha zd zd zd zd zd zd zd zd zd zd zd zd zb",
		"zb zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zc zd hb hb hb hb hb hb",
		"zb zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd hb hb hb hb hb hb",
		"zb zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zb",
		"zb zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zb",
		"zb zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zb",
		"zb zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zb",
		"zb zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zb"
	};

	const char Level_1_Set2[16][75] =
	{
		"zb zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zb",
		"zb zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zb",
		"zb zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zb",
		"zb zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zb",
		"zb zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zb",
		"zb zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zb",
		"zb zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zb",
		"zb zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zb",
		"zb zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zb",
		"zb zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zb",
		"zb zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zb",
		"zb zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zb",
		"zb zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zb",
		"zb zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zb",
		"zb zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zb",
		"zb zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zb",
	};

	const char Level_1_Set3[16][75] =
	{
		"zb zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zb",
		"zb zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zb",
		"zb zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zb",
		"zb zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zb",
		"zb zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zb",
		"zb zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zb",
		"zb zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zb",
		"zb zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zb",
		"zb zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zb",
		"zb zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zb",
		"zb zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zb",
		"zb zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zb",
		"zb zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zb",
		"zb zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zb",
		"zb zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zb",
		"zb zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zd zb",
	};

	const PhaseTileMap overlays_1[] =
	{
		{Level_1_Set1, phase_switch_lvl::lvl_1Set1 },
		{Level_1_Set2, phase_switch_lvl::lvl_1Set2 },
		{Level_1_Set3, phase_switch_lvl::lvl_1Set3 }
	};

	const Collider colliders_1[] =
	{
		Collider{{0.0f, 256.0f},{384.0f,260.0f},ColliderType::OneWay,phase_switch_lvl::lvl_1Set1},
		Collider{{0.0f, 64.0f},{63.0f,95.0f},ColliderType::Solid,phase_switch_lvl::lvl_1Set1},
		Collider{{672.0f, 64.0f},{800.0f,68.0f},ColliderType::OneWay,phase_switch_lvl::lvl_1Set1},
		Collider{{608.0f, 288.0f},{800.0f, 352.0f},ColliderType::Solid,phase_switch_lvl::lvl_1Set1},
		Collider{{110.0f, 140.0f},{250.0f,175.0f},ColliderType::Solid,phase_switch_lvl::lvl_1Set2},
		Collider{{315.0f, 70.0f},{440.0f,90.0f},ColliderType::Solid,phase_switch_lvl::lvl_1Set2},
		Collider{{505.0f, 10.0f},{510.0f,140.0f},ColliderType::Solid,phase_switch_lvl::lvl_1Set2},
		Collider{{660.0f, 85.0f},{800.0f,120.0f},ColliderType::Solid,phase_switch_lvl::lvl_1Set2},
		Collider{{345.0f, 260.0f},{440.0f,330.0f},ColliderType::OneWay,phase_switch_lvl::lvl_1Set2},
		Collider{{585.0f, 170.0f},{650.0f,220.0f},ColliderType::Solid,phase_switch_lvl::lvl_1Set2},
		Collider{{358.0f, 412.0f},{445.0f, 471.0f},ColliderType::Solid,phase_switch_lvl::lvl_1Set2},
		Collider{{572.0f, 391.0f},{627, 448},ColliderType::Solid,phase_switch_lvl::lvl_1Set2},
		Collider{{702.0f, 301},{768.0f, 358.0f},ColliderType::Solid,phase_switch_lvl::lvl_1Set2},
		Collider{{0.0f, 42.0f},{70.0f,60.2f},ColliderType::OneWay,phase_switch_lvl::lvl_1Set3},
		Collider{{8.0f, 193.0f},{76.0f,219.2f},ColliderType::Solid,phase_switch_lvl::lvl_1Set3},
		Collider{{24.0f, 365.0f},{100.0f,436.0f},ColliderType::Solid,phase_switch_lvl::lvl_1Set3},
		Collider{{135.0f, 447.0f},{202.0f,471.2f},ColliderType::Solid,phase_switch_lvl::lvl_1Set3},
		Collider{{666.6f, 413.0f},{800.0f,444.4f},ColliderType::Solid,phase_switch_lvl::lvl_1Set3},
		Collider{{610.0f, 248.0f},{673.0f,401.2f},ColliderType::Solid,phase_switch_lvl::lvl_1Set3},
		Collider{{335.0f, 236.0f},{449.0f,355.2f},ColliderType::Solid,phase_switch_lvl::lvl_1Set3},
		Collider{{496.0f, 133.0f},{520.0f,240.2f},ColliderType::Solid,phase_switch_lvl::lvl_1Set3},
		Collider{{777.0f, 277.0f},{800.0f,341.0f},ColliderType::Solid,phase_switch_lvl::lvl_1Set3},
		Collider{{577.0f, 48.0f},{610.0f,139.2f},ColliderType::Solid,phase_switch_lvl::lvl_1Set3},
		Collider{{629.0f, 102.0f},{706.4f,127.2f},ColliderType::Solid,phase_switch_lvl::lvl_1Set3},
		Collider{{0.0f, -250.0f},{800.0f,0.0f},ColliderType::Solid,phase_switch_lvl::any},
		Collider{{0.0f, 512.0f},{800.0f,1024.0f},ColliderType::Floor,phase_switch_lvl::any}
	};

	 Pickup pickups_1[] =
	{
		Pickup{15.0f,40.0f, 48,phase_switch_lvl::lvl_1Set1,PickupType::big},
		Pickup{670.0f,0.0f, 48,phase_switch_lvl::lvl_1Set1,PickupType::normal},
		Pickup{600.0f,245.0f, 48,phase_switch_lvl::lvl_1Set1,PickupType::normal},
		Pickup{335.0f,12.0f, 48,phase_switch_lvl::lvl_1Set2,PickupType::big},
		Pickup{700.0f,24.0f, 48,phase_switch_lvl::lvl_1Set2,PickupType::big},
		Pickup{715.0f,250.0f, 48,phase_switch_lvl::lvl_1Set2,PickupType::normal},
		Pickup{360.0f,220.0f, 48,phase_switch_lvl::lvl_1Set2,PickupType::normal},
		Pickup{6.0f,6.0f, 48,phase_switch_lvl::lvl_1Set3,PickupType::normal},
		Pickup{690.0f,380.0f, 48,phase_switch_lvl::lvl_1Set3,PickupType::normal},
		Pickup{650.0f,16.0f, 48,phase_switch_lvl::lvl_1Set3,PickupType::big}
	};

	int Tilemap_with = 288;

	void DrawTile(int tx, int ty, Surface* screen, int x, int y)
	{
		Pixel* src = tiles.GetBuffer() + tx * 32 + (ty * 32) * Tilemap_with;
		Pixel* dst = screen->GetBuffer() + x + y * 800;
		for (int i = 0; i < 32; i++)
			for (int j = 0; j < 32; j++)
			{
				// Check alpha threshold.
				unsigned char a = (src[j + i * Tilemap_with] >> 24) & 0xFF;
				if (a > 128)
					dst[j + i * 800] = src[j + i * Tilemap_with];

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
	
	void Level::SwichPhase(int activePhase)
	{
		auto allPickups = GetPickup();

		
		for (auto& p : allPickups)
		{
			// 3. Logic check
			bool isAny = (p.ps_type == phase_switch_lvl::any);
			bool isMatch = (static_cast<int>(p.ps_type) == activePhase);

			if (isAny || isMatch)
			{
				p.active = true; 
			}
			else
			{
				p.active = false;
			}
		}
	}

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
		{
			for (int x = 0; x < 25; x++)
			{
				int tx = Level_1[y][x * 3] - 'a';
				int ty = Level_1[y][x * 3 + 1] - 'a';
				DrawTile(tx, ty, screen, x * 32, y * 32);

			}
		}

		for (const auto& map : overlays_1)
		{
			if(static_cast<int>(map.phase) == activePhase)
			{
				for (int y = 0; y < 16; y++)
				{
					for (int x = 0; x < 25; x++)
					{
						char c1 = map.data[y][x * 3];
						char c2 = map.data[y][x * 3 + 1];

						if (c1 == 'z') continue;

						int tx = c1 - 'a';
						int ty = c2 - 'a';

						if (tx >= 0 && tx < 9 && ty >= 0 && ty < 4)
						{
							DrawTile(tx, ty, screen, x * 32, y * 32);
						}
					}
				}
				break;
			}
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
