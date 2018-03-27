#include "stdafx.h"
#include "ActionManager.h"

ActionManager::ActionManager(HWND wowWindowHandler)
{
	this->wowWindowHandler = wowWindowHandler;
}


ActionManager::~ActionManager()
{
}

void ActionManager::startAction(Action action)
{
	PostMessage(wowWindowHandler, WM_KEYDOWN, action, 0);
}

void ActionManager::stopAction(Action action)
{
	PostMessage(wowWindowHandler, WM_KEYUP, action, 0);
}
