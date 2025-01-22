#ifndef LIME_UI_GAMEPAD_H
#define LIME_UI_GAMEPAD_H


namespace lime {


	class Gamepad {

		public:

			struct GamepadGUIDInfo {
					uint16_t vendor;
					uint16_t product;
					uint16_t version;
					uint16_t crc16;
			};

			static void AddMapping (const char* content);
			static const char* GetDeviceGUID (int id);
			static const char* GetDeviceName (int id);
			static int GetVendor (int id);
			static int GetProduct (int id);
			static int GetProductVersion (int id);
			static int GetFirmwareVersion (int id);
			static const char* GetSerial (int id);
			static const char* GetRawPath (int id);
			static void GetGUIDInfo (int id, Gamepad::GamepadGUIDInfo *info);
			static int GetType (int id);
			static uint64_t GetDeviceSteamInputHandle (int id);

	};


}


#endif