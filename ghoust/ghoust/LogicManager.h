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
		static const float logicFrameRate;

		PlayerObject* character;

	private:
		void run();

		float findDirection(Position* characterPosition, Position* targetPosition);
		void follow(PlayerObject* target);
};
