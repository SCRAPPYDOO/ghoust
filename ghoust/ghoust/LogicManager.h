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

		static const int logicFrameRate = 17;

		Logic* characterLogic;

	public:
		void run();
};
