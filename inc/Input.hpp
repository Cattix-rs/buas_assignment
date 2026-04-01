#pragma once
#include <SDL.h>

namespace Tmpl8
{
	class Input
	{
	public:
		static void SendKeyDown(int scancode)
		{
			keys[scancode] = true;
		}

		static void SendKeyUp(int scancode)
		{
			keys[scancode] = false;
		}

		
        static void Update() {
            for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
                prevKeys[i] = keys[i];
            }
        }
        //holdable for x movement
        static bool Left() { return IsDown(SDL_SCANCODE_LEFT); }
        static bool Right() { return IsDown(SDL_SCANCODE_RIGHT); }

        // misalanious keys that are needed
        static bool BackSpace() { return IsPressed(SDL_SCANCODE_BACKSPACE); }
        static bool End() { return IsPressed(SDL_SCANCODE_END); }
        static bool Enter() { return IsPressed(SDL_SCANCODE_RETURN); }
        static bool Space() { return IsPressed(SDL_SCANCODE_SPACE); }
        // for naming
        static bool A()  { return IsPressed(SDL_SCANCODE_A); } 


        static bool AnyKeyDown() {
            for (int i = 0; i < SDL_NUM_SCANCODES; i++) 
            {
                if (keys[i]) return true;
            }
            return false;
        }

    private:
        static bool keys[SDL_NUM_SCANCODES];
        static bool prevKeys[SDL_NUM_SCANCODES];

        static bool IsDown(int scancode)
        {
            return keys[scancode];
        }

        static bool IsPressed(int scancode)
		{
            return keys[scancode] && !prevKeys[scancode];
        }

	};
}
