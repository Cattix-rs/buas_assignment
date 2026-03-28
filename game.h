#pragma once
#include <Level.hpp>
#include <Timer.hpp>
#include <physics.hpp>
namespace Tmpl8 {

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

	enum GameState
	{
		PLAYING,
		NAMING,
		SHOW_SCORES
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
	void KeyUp( int key ) { /* implement if you want to handle keys */ }
	void KeyDown( int key ) { /* implement if you want to handle keys */ }

	bool WasKeyPressed(int vKey);
	void HandleTyping();

	int GetCurrentPhase() const { return currentPhase; }
	
	void SavePlayerData(const char* name, uint32_t score);
	void LoadScores();
	void DrawScores();
	
	int currentPhase = 0;
private:
	std::string playerName = "";
	std::vector<HighScoreEntry> m_HighScores;
	bool m_prevKeystate[256] = {false};
	uint32_t playerScore = 0;


	GameState CurrentState = PLAYING;
	char m_CurrentName[6] = "";
	Surface* screen = nullptr;
	Timer timer;
	Level level;
	Physics gamephysics;
	float msAccumulator = 0.0f;
	const float Tick_Rate_100ms = 100.0f;
	int TickCounter;
	
};

}; // namespace Tmpl8