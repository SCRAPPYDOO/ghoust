// ghoust.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "ActionManager.h"
#include "WindowManager.h"
#include "ObjectManager.h"

using namespace std;

int main()
{
	WindowManager* windowManager = new WindowManager();

	//MemoryReader* memoryReader = new MemoryReader(windowManager->getProcessId());
	//MemoryReader::getInstance();

	ObjectManager::getInstance();

	ActionManager* actionManager = new ActionManager(windowManager->getWindowHandler());

	/*for (int i = 0; i < 200; i++) {
		actionManager->startAction(Action::MOVE_LEFT);
		Sleep(100);
		actionManager->stopAction(Action::MOVE_LEFT);
		Sleep(10000);
	}*/

	getchar();
	return 0;

}