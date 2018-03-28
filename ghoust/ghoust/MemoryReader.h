#pragma once

#include <iostream>
#include <Windows.h>

enum CHARACTERS_GUID {
	GHOUSTHUNTER_GUID = 1149344,
	ABIGAIL_GUID = 1143598,
	SHINAIRI_GUID = 1143511
};

enum STATIC_POINTER {
	PLAYER_GUID = 0x00C4DA98, //OK
	TARGET_GUID = 0x00B4E2D8, //OK

	STATIC_FLOAT_PLAYER_POS_X = 0x00C7B548,
	STATIC_FLOAT_PLAYER_POS_Y = 0x00C7B544,
	STATIC_FLOAT_PLAYER_POS_Z = 0x00C7B54C,
	/*
		B4E2C8 - Current Object Track Guid
		B4E2D0 - Interact Target Guid
		B4E2D8 - Locked Target Guid
		B4E2E8 - Last Enemy Target Guid
	*/
};

enum Address {
	WOW_BASE = 0x0400000,

	PLAYER_BASE = WOW_BASE + 0x34 + 0x24,

	PLAYER_LEVEL = (PLAYER_BASE + 0x8) + (0x35 * 4),

	PLAYER_POSITION_X = PLAYER_BASE + 0x09B8,
	PLAYER_POSITION_Y = PLAYER_BASE + 0x09BC,
	PLAYER_POSITION_Z = PLAYER_BASE + 0x09C0,

	PLAYER_CURRENT_XP = 0xB30,

	PLAYER_HEALTH = PLAYER_BASE + 0x00000016 * 4,

	CLIENT_CONNECTION = 0x011CB310,

	/*
		Object manager offsets
	*/

	OBJECT_MANAGER = 0x00B41414,
	FIRST_OBJECT = 0xac,
	NEXT_OBJECT = 0x3c,

	OBJECT_TYPE = 0x14,
	OBJECT_GUID = 0x30,

	/*
		End of Object manager offsets
	*/

	DESCIPROT = 0x8,

	OBJECT_HEALTH = 0x58
};

class MemoryReader
{
	public:
		static MemoryReader* getInstance();
		~MemoryReader();
		virtual ~MemoryReader() {
			this->stop();
		}

	private:
		MemoryReader();

		static MemoryReader* memoryReader;

		void initialize();
		void stop();
		void lookupPrivilege();
		void openProcess();
		void calculateWowBaseAddress();
		void calculateWowBaseAddress2();

	private:
		HANDLE processHandler;

	public:
		void readMemory();
		int readInt(Address address);

		float readFloat(Address address);

		int readInt(LPVOID address);
		int readInt(int address);
};
