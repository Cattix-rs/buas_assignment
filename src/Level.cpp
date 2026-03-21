#include <Level.hpp>

namespace Tmpl8
{

	namespace
	{
		Surface tiles("assets/pixelart-drawing_14.png");
		Sprite pickupSprite(new Surface("assets/energon_pickup_48x48.png"), 1);
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
		Collider{{0.0f, 200.0f},{400.0f,232.0f},ColliderType::OneWay},

		Collider{{0.0f, 511.9f},{800.0f,512.0f},ColliderType::Floor}
	};

	const Pickup pickups_1[] =
	{
		Pickup{200.0f,450.0f, 48}
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

	void Level::Init()
	{

		colliderCount = 0;   
		pickupCount = 0;     

		for (const Collider& c : colliders_1)
		{
			AddCollider(c);
		}

		for (const Pickup& p : pickups_1)
		{
			AddPickup(p);
		}
	}

	void Level::Draw(Surface* screen)
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
			if (!pickups[i].active)continue;

			pickupSprite.Draw(
				screen,
				static_cast<int>(pickups[i].pos.x),
				static_cast<int>(pickups[i].pos.y)
			);
		}
	}
	//std::span< Pickup> Level::GetPickup()
	//{
	//	return pickups_1; //non const refrence
	//}

	std::span<const Collider> Level::GetColliders() const
	{
		return std::span<const Collider>(colliders.data(), colliderCount);
	}
}
