#pragma once

#include <Windows.h>

// https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
enum Action {
	MOVE_FORWARD = 0x57,
	MOVE_LEFT = 0x41,
	MOVE_RIGHT = 0x44,
	MOVE_BACK = 0x53
};

class ActionManager
{
	public:
		ActionManager(HWND wowWindowHandler);
		~ActionManager();

	private:
		HWND wowWindowHandler;

	public:
		void startAction(Action action);
		void stopAction(Action action);
};

