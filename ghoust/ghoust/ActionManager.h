#pragma once

#include <Windows.h>

#include "ActionType.h"
#include "WindowManager.h"

class ActionManager
{
	public:
		static ActionManager* getInstance();
		~ActionManager();

	private:
		ActionManager();
		static ActionManager* actionManager;

	public:
		void startAction(int action);
		void stopAction(int action);
};
