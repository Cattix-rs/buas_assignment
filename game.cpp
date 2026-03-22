#include "game.h"
#include "surface.h"
#include <timer.hpp>
#include <physics.hpp>

#include <Player.hpp>

#include <cstdio> //printf
#include <iostream>
#include <ostream>
#include <windows.h>

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
		currentPhase = 0;
		// initialize movement/animation system with sprite and position pointers
		level.Init();
		player.Init(&theSprite, 0, 400);
		
		
		
		
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
	
	static Physics u_physics;
	
	void Game::Tick(float deltaTime)
	{
		timer.tick([&](double dt)
			{
				player.Update(static_cast<float>(dt));

				gamephysics.ResolvePlayerCollision(player, level, static_cast<float>(dt),currentPhase);
				gamephysics.CheckPickupCollision(player, level);
			});
		#ifdef _DEBUG
		timer.limitFPS(60); //  FPS cap
		
		#endif

		msAccumulator += deltaTime;
		while (msAccumulator >= Tick_Rate_100ms)
		{
			TickCounter++;
			msAccumulator -= Tick_Rate_100ms;

			if (TickCounter % 1 == 0)
			{
				printf("PHASE SWAP: Current Phase is now %d\n", currentPhase + 1);
				currentPhase = (currentPhase + 1) % 3;
 				TickCounter = 0;

				level.SwichPhase(currentPhase);
				
			}
		}

		screen->Clear(0);
		player.Update(deltaTime);
		
		gamephysics.ResolvePlayerCollision(player, level, deltaTime, currentPhase);
		gamephysics.CheckPickupCollision(player, level);
		

		level.Draw(screen, currentPhase);
		
		
		
		for (const auto& c : level.GetColliders())
		{
			bool isAny = (c.ps_type == phase_switch_lvl::any);
			bool isMatch = (static_cast<int>(c.ps_type) == currentPhase);
			if (isAny || isMatch)
			{
				if (c.type == ColliderType::Solid)
					screen->Box(c.box, 0xFF0000FF);
				else if (c.type == ColliderType::OneWay)
				{
					screen->Box(c.box, 0xFF2E8B57);
				}
				else if (c.type == ColliderType::Floor)
					screen->Box(c.box, 0x00000000);
			}
			
		}
		
		player.Draw(screen);
		
		theSprite.Draw(screen, player.GetX(), player.GetY());
		
		
		
		screen->Box(player.GetAABB(), 0xffffffff);
		player.clampToScreen();
		
	}

	
};/// making sure it renders and compiles


//tiled https://discord.com/channels/515453022097244160/1407719742541922374/1467979701610877102 https://discord.com/channels/515453022097244160/1407719742541922374/1467979756602527921