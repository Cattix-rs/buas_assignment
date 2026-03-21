#include "game.h"
#include "surface.h"
#include <timer.hpp>
#include <physics.hpp>

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
		level.Init();
		player.Init(&theSprite, 0, 0);
		
		
		
		
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
		
	

		screen->Clear(0);
		
		physics.ResolvePlayerCollision(player, level, deltaTime);
		physics.CheckPickupCollision(player, level);
		

		player.Update(deltaTime);
		
		level.Draw(screen);
		
		

		player.Draw(screen);
		
		theSprite.Draw(screen, player.GetX(), player.GetY());
		screen->Box(player.GetAABB(), 0xffffffff);
		screen->Line(0.0f, 200.0f, 232.0f, 200.0f, 0xffffffff);
	}
};/// making sure it renders and compiles


//tiled https://discord.com/channels/515453022097244160/1407719742541922374/1467979701610877102 https://discord.com/channels/515453022097244160/1407719742541922374/1467979756602527921