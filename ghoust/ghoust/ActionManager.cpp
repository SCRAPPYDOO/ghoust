#include "stdafx.h"
#include "ActionManager.h"

ActionManager* ActionManager::actionManager = NULL;

ActionManager* ActionManager::getInstance() {
	if(this->actionManager == NULL) {
		actionManager = new ActionManager();
	}

	return this->actionManager;
}

ActionManager::ActionManager()
{

}


ActionManager::~ActionManager()
{
}

void ActionManager::startAction(Action action)
{
	WindowManager::getInstance()->postMessage(action, WM_DOWN);
}

void ActionManager::stopAction(Action action)
{
	WindowManager::getInstance()->postMessage(action, WM_KEYUP);
}
