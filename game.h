#pragma once
#include <Level.hpp>
#include <Timer.hpp>
#include <physics.hpp>
/// this file has AI genarated code example Gemini.
#include "Input.hpp"

namespace Tmpl8 {
	// Highscore components
	struct HighScoreEntry
	{
		char name[6];
		uint32_t score;

		HighScoreEntry(const char* n, uint32_t s) : score(static_cast<uint32_t>(s))
		{
			strncpy(name, n, 5);
			name[5] = '\0';
		}
		HighScoreEntry() : score(0)
		{
			name[0] = '\0';
		}
	};

	enum GameState//actual state of the game
	{
		PLAYING,
		NAMING,
		SHOW_SCORES,
		TUTORIAL

	};

class Surface;
class Game
{
public:
	void SetTarget( Surface* surface ) { screen = surface; }
	void Init();
	void Shutdown();
	void Tick( float deltaTime );
	void MouseUp( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseDown( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseMove( int x, int y ) { /* implement if you want to detect mouse movement */ }
	void KeyUp( int key ) { Input::SendKeyUp(key); }
	void KeyDown(int key) { Input::SendKeyDown(key); }
	void Draw();

	void Restart();//restart without need for tutorial
	void HandleTyping();

	int GetCurrentPhase() const { return currentPhase; }//phase is a thing used for Collider and pickup rotating in sets
	
	void SavePlayerData(const char* name, uint32_t score);
	void LoadScores();
	void DrawScores();
	
	int currentPhase = 0;//initialized currentphase
private:
	std::string playerName = "";
	std::vector<HighScoreEntry> m_HighScores;// a Vector of all highscores that get saved in runtime needed cause truncation
	uint32_t playerScore = 0;


	GameState CurrentState = TUTORIAL;
	char m_CurrentName[6] = "";
	Surface* screen = nullptr;
	Timer timer;
	Level level;
	Physics gamephysics;
	float msAccumulator = 0.0f;
	const float Tick_Rate_100ms = 100.0f; // a timer and
	int TickCounter;
	
};

}; // namespace Tmpl8