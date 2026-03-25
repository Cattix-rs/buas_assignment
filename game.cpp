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
        deltaTime = Min(deltaTime, 33.3333f); // clamp deltaTime to avoid large jumps

		msAccumulator += deltaTime;
		while (msAccumulator >= Tick_Rate_100ms)
		{
			TickCounter++;
			msAccumulator -= Tick_Rate_100ms;

			if (TickCounter % 70 == 0)
			{
				printf("PHASE SWAP: Current Phase is now %d\n", currentPhase + 1);
				currentPhase = currentPhase  % 3 +1;
 				TickCounter = 0;

				level.SwichPhase(currentPhase);
				
				printf("Swapped to Phase %d: Pickups Reactivated!\n", currentPhase);
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
		
	}

	
};/// making sure it renders and compiles


//tiled https://discord.com/channels/515453022097244160/1407719742541922374/1467979701610877102 https://discord.com/channels/515453022097244160/1407719742541922374/1467979756602527921