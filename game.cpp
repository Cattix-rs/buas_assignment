#include "game.h"
#include "surface.h"
#include <timer.hpp>

#include <Player.hpp>

#include <cstdio> //printf
#include <iostream>
#include <ostream>

namespace Tmpl8
{
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	namespace
	{
		Sprite theSprite(new Surface("assets/WALK.PNG"), 8);
		int px = 0, py = 0;

		//Movement instance (onc per controlled entity;
		Player player;
	}
	void Game::Init()
	{
		// initialize movement/animation system with sprite and position pointers
		player.Init(&theSprite, 0, 0);
		level.Init();
		player.SetLevel(&level);
		
		
		// If sprite may change at runtime, update stored sprite size:
		player.SetSizeFromSprite();
	}
	
	
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
		
	}

	
	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------

	
	//int i;
	
	void Game::Tick(float deltaTime)
	{
		timer.tick([&](double dt)
			{
				player.Update(static_cast<float>(dt));
			});

		timer.limitFPS(90); // frame limiter
	

		screen->Clear(0);
		
		if (level)
		{
			onGround = false;
			// ----------- X AXIS COLLISION -----------
			pos.x += v.x * deltaTime;

			AABB playerBox = getAABB();
			AABB prevBox = aabb + prevPos;

			for (const Collider& c : level->GetColliders())
			{
				auto result = playerBox.overlap(c.box);
				if (!result) continue;

				vec2f correction = *result;

				if (correction.x != 0.0f)
				{
					pos.x -= correction.x;
					v.x = 0.0f;

					playerBox = getAABB(); // update box after correction
				}
			}

			// ----------- Y AXIS COLLISION -----------
			pos.y += v.y * deltaTime;

			playerBox = getAABB();

			for (const Collider& c : level->GetColliders())
			{
				auto result = playerBox.overlap(c.box);
				if (!result) continue;

				vec2f correction = *result;

				if (c.type == ColliderType::OneWay)
				{
					// check prev frame was max player <= min collider
					if (v.y <= 0) continue;

					if (prevBox.max.y > c.box.min.y)
						continue;
				}

				if (correction.y > 0.0f)
				{
					onGround = true;
				}

				if (correction.y != 0.0f)
				{
					pos.y -= correction.y;
					v.y = 0.0f;

					playerBox = getAABB();
				}
			}
		}
		if (level)
		{
			AABB playerBox = getAABB();

			for (Pickup& p : level->GetPickup())
			{
				if (!p.active) continue;

				if (playerBox.overlap(p.GetAABB()))
				{
					p.active = false;
					AddEnergon(25.0f);
				}
			}
		}

		player.Update(deltaTime);
		
		level.Draw(screen);
		
		

		player.Draw(screen);
		
		theSprite.Draw(screen, player.GetX(), player.GetY());
		screen->Box(player.getAABB(), 0xffffffff);
		screen->Line(0.0f, 200.0f, 232.0f, 200.0f, 0xffffffff);
	}
};/// making sure it renders and compiles


//tiled https://discord.com/channels/515453022097244160/1407719742541922374/1467979701610877102 https://discord.com/channels/515453022097244160/1407719742541922374/1467979756602527921