#include "stdafx.h"
#include "ActionManager.h"

ActionManager* ActionManager::actionManager = NULL;

ActionManager* ActionManager::getInstance() {
	if(actionManager == NULL) {
		actionManager = new ActionManager();
	}

	return actionManager;
}

ActionManager::ActionManager()
{

}


ActionManager::~ActionManager()
{
}

void ActionManager::startAction(ActionType action)
{
	WindowManager::getInstance()->postMessage(action, WM_KEYDOWN);
}

void ActionManager::stopAction(ActionType action)
{
	WindowManager::getInstance()->postMessage(action, WM_KEYUP);
}
