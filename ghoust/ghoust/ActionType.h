#pragma once

// https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx


enum KeyBinding {
	ONE = 0x31,
	TWO = 0x32,
	THREE = 0x33,
	FOUR = 0x34,
	FIVE = 0x35,
	SIX = 0x36,
	SEVEN = 0x37,
	EIGHT = 0x38,
	NINE = 0x39,
	ZERO = 0x30,
	MINUS = 0x2D,
	PLUS = 0x2B,
	
	W = 0x57,
	A = 0x41,
	S = 0x53,
	D = 0x44,

	NUMLOCK = 0x90,
};

class ActionType {
	public: 
		static const int NO_ACTION = 0x00000001;
		static const int MOVE_FORWARD = KeyBinding::W;
		static const int MOVE_LEFT = KeyBinding::A;
		static const int MOVE_RIGHT = KeyBinding::D;
		static const int MOVE_BACK = KeyBinding::S;
		static const int MOVE_AUTORUN = KeyBinding::NUMLOCK;
};

class WarlockActionType : public ActionType {
	public: 
		static const int CAST_DEMON_SKIN = KeyBinding::NINE;
};