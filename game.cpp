#include "game.h"
#include "surface.h"

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
		// Set hitbox insets (smaller values => larger hitbox; zero => full sprite)
		player.SetHitBoxInsets(22.0f, 18.0f);

		// If sprite may change at runtime, update stored sprite size:
		player.SetSizeFromSprite();
	}
	
	
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
		
	}

	namespace
	{
		Surface tiles("assets/Starry_Night_tiles_and_sprites.png");
	}
	
	


	char map[10][48] = {
		"aa ba ca da ea fa ga ha aa ba ca da ea fa ga ha",
		"ab bb cb db eb fb gb hb ab bb cb db eb fb gb hb",
		"ac bc cc dc ec fc gc hc ac bc cc dc ec fc gc hc",
		"ad bd cd dd ed fd gd hd ad bd cd dd ed fd gd hd",
		"ae be ce de ee fe ge he ae be ce de ee fe ge he",
		"aa ba ca da ea fa ga ha aa ba ca da ea fa ga ha",
		"ab bb cb db eb fb gb hb ab bb cb db eb fb gb hb",
		"ac bc cc dc ec fc gc hc ac bc cc dc ec fc gc hc",
		"ad bd cd dd ed fd gd hd ad bd cd dd ed fd gd hd",
		"ae be ce de ee fe ge he ae be ce de ee fe ge he",
	};
	void DrawTile(int tx, int ty, Surface* screen, int x, int y)
	{
		Pixel* src = tiles.GetBuffer() + tx * 32 + (ty * 32) * 256;
		Pixel* dst = screen->GetBuffer() + x + y * 800;
		for (int i = 0; i < 32; i++)
			for (int j = 0; j < 32; j++)
			{
				// Check alpha threshold.
				unsigned char a = (src[j + i * 256] >> 24) & 0xFF;
				if (a > 128)
					dst[j + i * 800] = src[j + i * 256];

			}
	}
	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	//Sprite theSprite(new Surface("assets/ctankbase.tga"), 16);
	//Sprite theSprite(new Surface("assets/ctankbase.tga"), 16);
	//Sprite theSprite(new Surface("assets/ctankbase.tga"), 16);
	//Sprite theSprite(new Surface("assets/ctankbase.tga"), 16);
	//Sprite theSprite(new Surface("assets/ctankbase.tga"), 16);
	//Sprite theSprite(new Surface("assets/ctankbase.tga"), 16);
	//Sprite theSprite(new Surface("assets/ctankbase.tga"), 16);
	
	//int i;
	
	void Game::Tick(float deltaTime)
	{
		screen->Clear(0);

		player.Update(deltaTime);
		for (int y = 0; y < 10; y++)
			for (int x = 0; x < 16; x++)
			{
				int tx = map[y][x * 3] - 'a';
				int ty = map[y][x * 3 + 1] - 'a';
				DrawTile(tx, ty, screen, x * 32, y * 32);
		
			}
		
		
		theSprite.Draw(screen, player.GetX(), player.GetY());
		screen->Box(player.getAABB(), 0xffffffff);
	}
};/// making sure it renders and compiles
//gaffer on games 
//sprisheet 
//phyiscs 
// met manon mail sturen naar buas for huidige education verification
// sprite animation base class all frames and all using vectors 
//aabb assing to player and edge of scr4een 
//tiled https://discord.com/channels/515453022097244160/1407719742541922374/1467979701610877102 https://discord.com/channels/515453022097244160/1407719742541922374/1467979756602527921