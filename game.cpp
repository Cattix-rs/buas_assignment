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


		Player player;
	}
	void Game::Init()
	{
		currentPhase = 0;
		CurrentState = PLAYING;
		
		level.Init();
		player.Init(&theSprite, 0, 400);
		LoadScores();
		
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
			for (const auto& entry : m_HighScores)
			{
				// Use "\n" instead of std::endl to avoid unnecessary disk flushing
				highscores << entry.name << " " << entry.score << "\n";
			}
		}
		highscores.close();
	}


	void Game::LoadScores()
	{
		
		std::ifstream Infile("highscores/highscores.txt");
		if (!Infile) return;

		std::string tempName;
		uint32_t tempScore;
		while (Infile >> tempName >> tempScore)
		{
			m_HighScores.emplace_back(tempName.c_str(), static_cast<uint32_t>(tempScore));
		}
		Infile.close();
	}

	void Game::DrawScores()
	{
		int  xPos = 200;
		int yPos = 150;

		const char* msgT25 = "   Top 25   ";
		screen->Print(msgT25, xPos + 25, yPos - 30, 0xffffff);

		for (size_t i = 0; i < m_HighScores.size(); ++i)
		{
			if (i == 10)
			{
				xPos = xPos + 300; // Move 300 pixels to the right
				yPos = 150;       // Reset height to the top
			}
			char buffer[64];

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
		player.debugShutdown();
	}

	void Game::Draw()
	{
		uint32_t score = player.GetScore();
		if (CurrentState == PLAYING)
		{
			
			char ScoreBuf[32];
			sprintf(ScoreBuf, "Score: %05u", score);
			screen->Print(ScoreBuf, 10, 10, 0xFFFF00);
		}
		else if (CurrentState == NAMING)
		{
			screen->Print("---Game Over---", 280, 100, 0xFF0000);

			char finalScore[32];
			sprintf(finalScore, "Final Score: %u", score);
			screen->Print(finalScore, 285, 120, 0xFFFF00);

			screen->Print("Enter a Short Name (5characters max)", 275, 160, 0xFFFFFF);

			char nameDisplay[16];
			if (strlen(m_CurrentName) == 0) sprintf(nameDisplay, "_ _ _ _ _");
			else if (strlen(m_CurrentName) == 1) sprintf(nameDisplay, "%c _ _ _ _", m_CurrentName[0]);
			else if (strlen(m_CurrentName) == 2) sprintf(nameDisplay, "%c %c _ _ _", m_CurrentName[0], m_CurrentName[1]);
			else if (strlen(m_CurrentName) == 3) sprintf(nameDisplay, "%c %c %c _ _", m_CurrentName[0], m_CurrentName[1], m_CurrentName[2]);
			else if (strlen(m_CurrentName) == 4) sprintf(nameDisplay, "%c %c %c %c _", m_CurrentName[0], m_CurrentName[1], m_CurrentName[2], m_CurrentName[3]);
			else sprintf(nameDisplay, "%c %c %c %c %c", m_CurrentName[0], m_CurrentName[1], m_CurrentName[2], m_CurrentName[3], m_CurrentName[4]);

			screen->Print(nameDisplay, 320, 190, 0x00FF00);

			if (strlen(m_CurrentName) > 2)
			{
				screen->Print("Press enter to save", 275, 230, 0x555555);
			}
			
			
		}
	}

	void Game::Restart()
	{
		CurrentState = PLAYING;
		currentPhase = 1;
		msAccumulator = 0.0f;
		TickCounter = 0;
		player.Reset();
		player.Init(&theSprite, 0, 400);
		
		m_CurrentName[0] = '\0';
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
		int len = strlen(m_CurrentName);

		if (WasKeyPressed(VK_BACK) && len > 0)
		{
			m_CurrentName[len - 1] = '\0';
		}
		if (len < 5)
		for (int vk = 0x41; vk <= 0x5A; ++vk)
		{
			if (WasKeyPressed(vk))
			{
				size_t len = strlen(m_CurrentName);
				if (len < 5)
				{
					m_CurrentName[len] = static_cast<char>(vk);
					m_CurrentName[len + 1] = '\0';
					break;
				}
			}
		}
		if (WasKeyPressed(VK_RETURN) && strlen(m_CurrentName) > 1) {
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
		screen->Clear(0);

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

					player.AddScore(6);

					printf("Swapped to Phase %d: Pickups Reactivated!\n", currentPhase);
				}

			}

#ifdef _DEBUG
			if (GetAsyncKeyState(VK_END) & 0x8000)
			{
				Shutdown();
			}
#endif
			
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
			screen->Print("PRESS R TO TRY AGAIN", 300, 400, 0x00FF00);

			if (WasKeyPressed('R'))
			{
				Restart();
			}
		}
		Draw();
	}

	
};/// making sure it renders and compiles


//tiled https://discord.com/channels/515453022097244160/1407719742541922374/1467979701610877102 https://discord.com/channels/515453022097244160/1407719742541922374/1467979756602527921