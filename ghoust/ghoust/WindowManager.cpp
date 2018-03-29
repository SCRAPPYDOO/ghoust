#include "stdafx.h"
#include "WindowManager.h"

#include <iostream>

using namespace std;

WindowManager* WindowManager::windowManager = NULL;

WindowManager* WindowManager::getInstance() {
	if(windowManager == NULL) {
		windowManager = new WindowManager();
	}

	return windowManager;
}

WindowManager::WindowManager()
{
	this->wowWindowHandler = FindWindow(0, TEXT("World of Warcraft"));

	if (this->wowWindowHandler == 0) {
		std::cerr << "Error cannot find window." << endl;
		getchar();
	}
	else {
		GetWindowThreadProcessId(this->wowWindowHandler, &this->processId);
	}

	if (this->getProcessId() == NULL) {
		cout << "WindowManager: Cant find process" << endl;
	}
	else {
		cout << "WindowManager: Process id: " << this->getProcessId() << endl;
	}
}

WindowManager::~WindowManager()
{
}

void WindowManager::postMessage(ActionType action, int keyStatus) {
	PostMessage(wowWindowHandler, keyStatus, action, 0);
}
