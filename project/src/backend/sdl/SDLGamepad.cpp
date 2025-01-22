#include "SDLGamepad.h"


namespace lime {


	std::map<int, SDL_GameController*> gameControllers = std::map<int, SDL_GameController*> ();
	std::map<int, int> gameControllerIDs = std::map<int, int> ();

	bool gameControllerExists (int id) {
		if(gameControllers.find (id) != gameControllers.end ()) {
			return true;
		} else {
			printf("SDLGamepad::gameControllerExists(%d) returned false!", id);
			return false;
		}
	}


	bool SDLGamepad::Connect (int deviceID) {

		if (SDL_IsGameController (deviceID)) {

			SDL_GameController *gameController = SDL_GameControllerOpen (deviceID);

			if (gameController) {

				SDL_Joystick *joystick = SDL_GameControllerGetJoystick (gameController);
				int id = SDL_JoystickInstanceID (joystick);

				gameControllers[id] = gameController;
				gameControllerIDs[deviceID] = id;

				return true;

			}

		}

		return false;

	}


	bool SDLGamepad::Disconnect (int id) {

		if (gameControllerExists(id)) {

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

		if (gameControllerExists(id)) {
			SDL_Joystick* joystick = SDL_GameControllerGetJoystick (gameControllers[id]);

			if (joystick) {

				char* guid = new char[64];
				SDL_JoystickGetGUIDString (SDL_JoystickGetGUID (joystick), guid, 64);
				return guid;

			}
		}

		return 0;

	}


	const char* Gamepad::GetDeviceName (int id) {

		if (gameControllerExists(id)) {
			return SDL_GameControllerName (gameControllers[id]);
		}

		return 0;

	}


	int Gamepad::GetVendor (int id) {

		if(gameControllerExists(id)) {
			return SDL_GameControllerGetVendor(gameControllers[id]);
		}

		return 0;

	}


	int Gamepad::GetProduct (int id) {

		if(gameControllerExists(id)) {
			return SDL_GameControllerGetProduct(gameControllers[id]);
		}

		return 0;

	}


	int Gamepad::GetProductVersion (int id) {

		if(gameControllerExists(id)) {
			return SDL_GameControllerGetProductVersion(gameControllers[id]);
		}

		return 0;

	}


	int Gamepad::GetFirmwareVersion (int id) {

		if(gameControllerExists(id)) {
			return SDL_GameControllerGetFirmwareVersion(gameControllers[id]);
		}

		return 0;

	}


	const char* Gamepad::GetSerial (int id) {

		if(gameControllerExists(id)) {
			return SDL_GameControllerGetSerial(gameControllers[id]);
		}

		return 0;

	}


	const char* Gamepad::GetRawPath (int id) {

		if(gameControllerExists(id)) {
			return SDL_GameControllerPath(gameControllers[id]);
		}

		return 0;

	}


	void Gamepad::GetGUIDInfo (int id, Gamepad::GamepadGUIDInfo *info) {

		if (gameControllerExists(id)) {
			SDL_Joystick* joystick = SDL_GameControllerGetJoystick (gameControllers[id]);

			if (joystick) {

				SDL_GetJoystickGUIDInfo (SDL_JoystickGetGUID (joystick), &info->vendor, &info->product, &info->version, &info->crc16);

			}
		}

	}


	int Gamepad::GetType (int id) {

		if (gameControllerExists(id)) {
			return SDL_GameControllerGetType(gameControllers[id]);
		}

		return SDL_CONTROLLER_TYPE_UNKNOWN;

	}


	uint64_t Gamepad::GetDeviceSteamInputHandle (int id) {

		if (gameControllerExists(id)) {
			return SDL_GameControllerGetSteamHandle(gameControllers[id]);
		}

		return 0;

	}

}