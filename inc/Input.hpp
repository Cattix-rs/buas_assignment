#pragma once
#include <SDL.h>
/// this file is partially made with AI generated code example Gemini, chatgpt

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

        static bool IsPressed(int scancode)
        {
            return keys[scancode] && !prevKeys[scancode];
        }
		
        static bool IsDown(int scancode)
        {
            return keys[scancode];
        }

        static void Update() {
            for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
                prevKeys[i] = keys[i];
            }
        }

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

        

       

	};
}
