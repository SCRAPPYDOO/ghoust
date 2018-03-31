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

		static const float degree;
		static const float pointDegree;
		static const float logicFrameRate;
		static const int startFollowRange = 8;
		static const int stopFollowRange = 5;
		static const float rotationDifferenceCheck;
		static const float rotationDifferenceToMove;

		PlayerObject* character;
		Logic* characterLogic;

	private:
		void run();

		float findDirection(Position* characterPosition, Position* targetPosition);
		float findRange(Position* characterPosition, Position* targetPosition);
		void follow(PlayerObject* target);
};
