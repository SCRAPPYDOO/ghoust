#include "stdafx.h"
#include "WindowManager.h"

#include <iostream>
#include <Windows.h>

using namespace std;

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
		cout << "Cant find process" << endl;
	}
	else {
		cout << "Process id: " << this->getProcessId() << endl;
	}
}

WindowManager::~WindowManager()
{
}
