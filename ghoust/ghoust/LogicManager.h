#pragma once

#include "ObjectManager.h"

class LogicManager
{
	public:
		static LogicManager* getInstance();
		~LogicManager();

	private:
		LogicManager();
		static LogicManager* logicManager;

		static const float degree;
		static const float pointDegree;

	private:
		void run();

		void getPosition();

		float findDirection(PlayerObject* target);
};
