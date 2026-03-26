#pragma once
#include <Level.hpp>
#include <Timer.hpp>
#include <physics.hpp>
namespace Tmpl8 {

	struct highscores
	{
		char name[5];
		uint32_t score;
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

	int GetCurrentPhase() const { return currentPhase; }
	
	void SavePlayerData();
	void LoadScores();
	void DrawScores();
	
	int currentPhase = 0;
private:
	std::string playerName = "";
	struct ScoreEntry { std::string name; int score; };
	std::vector<ScoreEntry> highScores;

	enum State
	{
		PLAYING,
		NAME_ENTRY,
		LEADERBOARD
	};
	State CurrentState = PLAYING;
	Surface* screen = nullptr;
	Timer timer;
	Level level;
	Physics gamephysics;
	float msAccumulator = 0.0f;
	const float Tick_Rate_100ms = 100.0f;
	int TickCounter;
	
};

}; // namespace Tmpl8