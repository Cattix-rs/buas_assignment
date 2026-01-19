#include "game.h"
#include "surface.h"
#include <cstdio> //printf
//#include <windows.h>
//#include <Player_input.cpp>



namespace Tmpl8
{
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
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
	//Sprite theSprite(new Surface("assets/ATTACK_1.PNG"), 6);
	int px = 0, py = 0;
	void Game::Tick(float deltaTime)
	{
		screen->Clear(0);
		for (int y = 0; y < 10; y++)
			for (int x = 0; x < 16; x++)
			{
				int tx = map[y][x * 3] - 'a';
				int ty = map[y][x * 3 + 1] - 'a';
				DrawTile(tx, ty, screen, x * 32, y * 32);
		
			}
		
		/*if (GetAsyncKeyState(VK_LEFT)) { px--; }
		if (GetAsyncKeyState(VK_RIGHT)) { px++; }
		if (GetAsyncKeyState(VK_UP)) { py--; }
		if (GetAsyncKeyState(VK_DOWN)) { py++; }*/
		//theSprite.Draw(screen, px, py);
	}
};/// making sure it renders and compiles
// tile map 
//gaffer on games 
//sprisheet 
//phyiscs 