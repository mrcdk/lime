#ifndef LIME_SDL_GAMEPAD_H
#define LIME_SDL_GAMEPAD_H


#include <SDL.h>
#include <ui/Gamepad.h>
#include <map>
#include <cstdio>


namespace lime {


	class SDLGamepad {

		public:

			static bool Connect (int deviceID, SDL_JoystickID *joystickId);
			static bool Disconnect (SDL_JoystickID id);

	};


}


#endif