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

		static const float logicFrameRate;

		PlayerObject* character;
		Logic* characterLogic;

	private:
		void run();
};
