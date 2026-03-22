#pragma once
#include <Level.hpp>
#include <Timer.hpp>
#include <physics.hpp>
namespace Tmpl8 {

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
	
	
	int currentPhase = 0;
private:
	Surface* screen = nullptr;
	Timer timer;
	Level level;
	Physics gamephysics;
	float msAccumulator = 0.0f;
	const float Tick_Rate_100ms = 100.0f;
	int TickCounter;
	
};

}; // namespace Tmpl8