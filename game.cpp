#include "game.h"

#include <algorithm>

#include "surface.h"
#include <timer.hpp>
#include <physics.hpp>
#include <Player.hpp>

#include <cstdio> //printf
#include <fstream>
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
		CurrentState = PLAYING;
		// initialize movement/animation system with sprite and position pointers
		level.Init();
		player.Init(&theSprite, 0, 400);
		
		
		
		
		// If sprite may change at runtime, update stored sprite size:
		player.SetSizeFromSprite();
		
	}

	void Game::SavePlayerData(const char* name, uint32_t score)
	{
		m_HighScores.emplace_back(name, score);

		std::sort(m_HighScores.begin(), m_HighScores.end(), [](const HighScoreEntry& a, const HighScoreEntry& b)
		{
			return a.score > b.score;
		});

		if (m_HighScores.size() > 25) m_HighScores.resize(25);

		std::ofstream highscores("highscores/highscores.txt", std::ios::trunc);

		if (highscores.is_open())
		{
			highscores.write(reinterpret_cast<char*>(m_HighScores.data()), m_HighScores.size() * sizeof(HighScoreEntry));
		}
		highscores.close();
	}


	void Game::LoadScores()
	{
		
		std::ifstream file("highscore/highscores.txt");
		if (!file) return;
		char tempName[6];
		uint32_t tempScore;
		while (file >> tempName >> tempScore)
		{
			m_HighScores.emplace_back(tempName, static_cast<uint32_t>(tempScore));
		}
		file.close();
	}

	void Game::DrawScores()
	{
		int  xPos = 200;
		int yPos = 150;

		const char* msgT25 = "   Top 25   ";
		screen->Print(msgT25, xPos + 25, yPos - 30, 0xffffff);

		for (size_t i = 0; i < m_HighScores.size(); ++i)
		{
			char buffer[32];

			sprintf(buffer, "%d. %s %u", static_cast<int>(i) + 1, m_HighScores[i].name, m_HighScores[i].score);
			screen->Print(buffer, xPos, yPos, 0x00ff00); 
			yPos += 20;
		}
	}

	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
		
	}

	bool Game::WasKeyPressed(int vKey)
	{
		bool isDown = (GetAsyncKeyState(vKey) & 0x8000) != 0;
		bool wasDown = m_prevKeystate[vKey];

		m_prevKeystate[vKey] = isDown;

		return (isDown && !wasDown);
	}

	void Game::HandleTyping()
	{
		for (int vk = 0x41; vk <= 0x5A; ++vk)
		{
			if (WasKeyPressed(vk))
			{
				size_t len = strlen(m_CurrentName);
				if (len < 5)
				{
					m_CurrentName[len] = (char)vk;
					m_CurrentName[len + 1] = '\0';
					printf("Name: %s\n", m_CurrentName);
				}
			}
		}
		if (WasKeyPressed(VK_RETURN) && strlen(m_CurrentName) == 3) {
			SavePlayerData(m_CurrentName, playerScore);
			CurrentState = SHOW_SCORES;
		}
	}
	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	
	static Physics u_physics;
	
	void Game::Tick(float deltaTime)
	{
        deltaTime = Min(deltaTime, 33.3333f); // clamp deltaTime to avoid large jumps

		if (CurrentState == PLAYING)
		{
			msAccumulator += deltaTime;
			while (msAccumulator >= Tick_Rate_100ms)
			{
				TickCounter++;
				msAccumulator -= Tick_Rate_100ms;

				if (TickCounter % 60 == 0)
				{
					printf("PHASE SWAP: Current Phase is now %d\n", currentPhase + 1);
					currentPhase = currentPhase % 3 + 1;
					TickCounter = 0;

					level.SwichPhase(currentPhase);

					player.AddScore(60);

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

			if (player.IsDead() && CurrentState == PLAYING)
			{
				int score = player.GetScore();
				CurrentState = NAMING;
				m_CurrentName[0] = '\0';
				this->playerScore = score;
				for (int i = 0; i < 256; i++) {
					m_prevKeystate[i] = (GetAsyncKeyState(i) & 0x8000) != 0;
				}
				const char* msg = "your energon is now zero (you lost). Score: %u. Switching to Naming. \n ";

				int msgX = 800 / 2 - 50;
				int msgY = 512 / 2 - 10;
				screen->Print(msg, msgX, msgY, 0xFF0000);

			}
		}
		else if (CurrentState == NAMING)
		{
			screen->Clear(0);
			HandleTyping();
		}
		else if (CurrentState == SHOW_SCORES)
		{
			DrawScores();
		}
		
	}

	
};/// making sure it renders and compiles


//tiled https://discord.com/channels/515453022097244160/1407719742541922374/1467979701610877102 https://discord.com/channels/515453022097244160/1407719742541922374/1467979756602527921