#include "SDLGamepad.h"


namespace lime {


	std::map<int, SDL_GameController*> gameControllers = std::map<int, SDL_GameController*> ();
	std::map<int, int> gameControllerIDs = std::map<int, int> ();
	std::map<int, int> steamInputGamepadIndex = std::map<int, int> ();

	static int getSteamInputGamepadIndexFromName(const char* name) {
		const char *digits = SDL_strstr(name, "pad ");
		if (digits) {
			digits += 4;
			if (SDL_isdigit(*digits)) {
				return SDL_atoi(digits);
			}
		}

		return -1;
	}


	bool SDLGamepad::Connect (int deviceID) {

		if (SDL_IsGameController (deviceID)) {

			SDL_GameController *gameController = SDL_GameControllerOpen (deviceID);

			if (gameController) {

				SDL_Joystick *joystick = SDL_GameControllerGetJoystick (gameController);
				int id = SDL_JoystickInstanceID (joystick);

				gameControllers[id] = gameController;
				gameControllerIDs[deviceID] = id;

				// On linux steam reports the virtual controller with the name: "Microsoft X-Box 360 pad <number>"
				// where <number> is the steam input gamepad index that can be used
				// with SteamInput()->GetControllerForGamepadIndex() to get the final steam controller id.
				// Info extracted from SDL here:
				// https://github.com/libsdl-org/SDL/blob/4b429b9fa71dfc5b1688e3f87620341d5f67c0f4/src/joystick/linux/SDL_sysjoystick.c#L222-L237
				// I've only tested it on the Steam Deck.
				const char* name = SDL_JoystickNameForIndex(deviceID);
				steamInputGamepadIndex[id] = getSteamInputGamepadIndexFromName(name);


				return true;

			}

		}

		return false;

	}


	bool SDLGamepad::Disconnect (int id) {

		if (gameControllers.find (id) != gameControllers.end ()) {

			SDL_GameController *gameController = gameControllers[id];
			SDL_GameControllerClose (gameController);
			gameControllers.erase (id);

			return true;

		}

		return false;

	}


	int SDLGamepad::GetInstanceID (int deviceID) {

		return gameControllerIDs[deviceID];

	}


	void Gamepad::AddMapping (const char* content) {

		SDL_GameControllerAddMapping (content);

	}


	const char* Gamepad::GetDeviceGUID (int id) {

		SDL_Joystick* joystick = SDL_GameControllerGetJoystick (gameControllers[id]);

		if (joystick) {

			char* guid = new char[64];
			SDL_JoystickGetGUIDString (SDL_JoystickGetGUID (joystick), guid, 64);
			return guid;
		}

		return 0;

	}


	const char* Gamepad::GetDeviceName (int id) {

		return SDL_GameControllerName (gameControllers[id]);

	}

	int Gamepad::GetPlayerIndex (int id) {

		return SDL_GameControllerGetPlayerIndex (gameControllers[id]);

	}

	int Gamepad::GetSteamInputGamepadIndex (int id) {

		if (steamInputGamepadIndex.count(id) > 0) {
			return steamInputGamepadIndex[id];
		} else {
			return -1;
		}

	}

}