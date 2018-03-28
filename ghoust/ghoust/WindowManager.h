#pragma once

#include <Windows.h>

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

		postMessage(Action action, int keyStatus);
};
