#pragma once

#include <Windows.h>
#include "ActionType.h"

class WindowManager
{
	public:
		static WindowManager* getInstance();
		~WindowManager();

	private:
		WindowManager();
		static WindowManager* windowManager;
		HWND wowWindowHandler;
		DWORD processId;

	public:
		DWORD getProcessId() { return processId; };
		HWND getWindowHandler() { return wowWindowHandler; };

		void postMessage(ActionType action, int keyStatus);
};
