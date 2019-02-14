#pragma once

#include "ObjectManager.h"
#include "Logic.h"

class LogicManager
{
	public:
		static LogicManager* getInstance();
		~LogicManager();

	private:
		LogicManager();
		static LogicManager* logicManager;

		Logic* characterLogic;

	public:
		void run();
};
