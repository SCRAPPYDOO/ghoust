#pragma once

enum STATIC_POINTER {
	PLAYER_GUID = 0x00C4DA98, //OK
	TARGET_GUID = 0x00B4E2D8, //OK

	STATIC_FLOAT_PLAYER_POS_X = 0x00C7B548,
	STATIC_FLOAT_PLAYER_POS_Y = 0x00C7B544,
	STATIC_FLOAT_PLAYER_POS_Z = 0x00C7B54C,

	STATIC_INT_PLAYER_CLASS = 0x827E81,

	/*
	leaderGuid = 0x00BC75F8,
	party1Guid = 0x00BC6F48,
	party2Guid = 0x00BC6F50,
	party3Guid = 0x00BC6F58,
	party4Guid = 0x00BC6F60,
	*/

	/*
	B4E2C8 - Current Object Track Guid
	B4E2D0 - Interact Target Guid
	B4E2D8 - Locked Target Guid
	B4E2E8 - Last Enemy Target Guid
	*/
};

enum Address {
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