#pragma once

#include <Windows.h>

class WindowManager
{
	public:
		WindowManager();
		~WindowManager();

	private:
		HWND wowWindowHandler;
		DWORD processId;

	public:
		DWORD getProcessId() { return processId; };
		HWND getWindowHandler() { return wowWindowHandler; };
};

