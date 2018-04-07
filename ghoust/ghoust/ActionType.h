#pragma once

enum KeyBinding {
	ZERO = 0x30,
	ONE = 0x31,
	TWO = 0x32,
	THREE = 0x33,
	FOUR = 0x34,
	FIVE = 0x35,
	SIX = 0x36,
	SEVEN = 0x37,
	EIGHT = 0x38,
	NINE = 0x39,
	MINUS = 0xBD,
	PLUS = 0xBB,

	W = 0x57,
	A = 0x41,
	S = 0x53,
	D = 0x44,

	Q = 0x51,

	SPACE = 0x20,
	TAB = 0x09,

	NUMLOCK = 0x90,
};

class ActionType {
	public: 
		static const int NO_ACTION = 0x00000001;

		/*
			MOVEMENT
		*/
		static const int MOVE_FORWARD = KeyBinding::W;
		static const int MOVE_LEFT = KeyBinding::A;
		static const int MOVE_RIGHT = KeyBinding::D;
		static const int MOVE_BACK = KeyBinding::S;
		static const int MOVE_AUTORUN = KeyBinding::NUMLOCK;
		static const int JUMP = KeyBinding::SPACE;

		/*
			EAT DRINK
		*/
		static const int EAT = KeyBinding::MINUS;
		static const int DRINK = KeyBinding::PLUS;

		/*
			COMBAT
		*/
		static const int TARGET_NEAREST_ENEMY = KeyBinding::TAB;
};

class WarlockActionType : public ActionType {
	public: 
		static const int CAST_DEMON_SKIN = KeyBinding::NINE;
		static const int CAST_SHADOW_BOLT = KeyBinding::TWO;
		static const int CAST_IMMOLATE = KeyBinding::ONE;
		static const int CAST_CORRUPTION = KeyBinding::THREE;
		static const int CAST_SUMMON_DEMON = KeyBinding::ZERO;
		static const int CAST_CURSE_OF_AGONY = KeyBinding::FOUR;
};