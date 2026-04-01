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
        static bool A() { return IsPressed(SDL_SCANCODE_A); } 
        static bool B() { return IsPressed(SDL_SCANCODE_B); }
        static bool C() { return IsPressed(SDL_SCANCODE_C); }
        static bool D() { return IsPressed(SDL_SCANCODE_D); }
        static bool E() { return IsPressed(SDL_SCANCODE_E); }
        static bool F() { return IsPressed(SDL_SCANCODE_F); }
        static bool G() { return IsPressed(SDL_SCANCODE_G); }
        static bool H() { return IsPressed(SDL_SCANCODE_H); }
        static bool I() { return IsPressed(SDL_SCANCODE_I); }
        static bool J() { return IsPressed(SDL_SCANCODE_J); }
        static bool K() { return IsPressed(SDL_SCANCODE_K); }
        static bool L() { return IsPressed(SDL_SCANCODE_L); }
        static bool M() { return IsPressed(SDL_SCANCODE_M); }
        static bool N() { return IsPressed(SDL_SCANCODE_N); }
        static bool O() { return IsPressed(SDL_SCANCODE_O); }
        static bool P() { return IsPressed(SDL_SCANCODE_P); }
        static bool Q() { return IsPressed(SDL_SCANCODE_Q); }
        static bool R() { return IsPressed(SDL_SCANCODE_R); }
        static bool S() { return IsPressed(SDL_SCANCODE_S); }
        static bool T() { return IsPressed(SDL_SCANCODE_T); }
        static bool U() { return IsPressed(SDL_SCANCODE_U); }
        static bool V() { return IsPressed(SDL_SCANCODE_V); }
        static bool W() { return IsPressed(SDL_SCANCODE_W); }
        static bool X() { return IsPressed(SDL_SCANCODE_X); }
        static bool Y() { return IsPressed(SDL_SCANCODE_Y); }
        static bool Z() { return IsPressed(SDL_SCANCODE_Z); }
      


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
