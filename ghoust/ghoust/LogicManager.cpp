#include "stdafx.h"

#include "LogicManager.h"
#include "ActionManager.h"
#include "LogicFactory.h"

#include <thread>
#include <math.h>

using namespace std;

LogicManager* LogicManager::logicManager = NULL;

const float LogicManager::degree = 0.01745325f;
const float LogicManager::pointDegree = 0.78f;
const float LogicManager::logicFrameRate = 17;
const float LogicManager::followMinRange = 7;
const float LogicManager::rotationDifferenceCheck = 0.16f;
const float LogicManager::rotationDifferenceToMove = 0.5f;

LogicManager* LogicManager::getInstance() {
	if(logicManager == NULL) {
		logicManager = new LogicManager();
	}

	return logicManager;
}

LogicManager::LogicManager() {
  cout << "LogicManager: Initializing" << endl;
  character = ObjectManager::getInstance()->getPlayer();
  if (character != NULL) {

	  characterLogic = LogicFactory::getLogic(character);
	  run();
  }
  else {
	  cout << "LogicManager: Cant find  character !" << endl;
  }
}

LogicManager::~LogicManager()
{
}

void LogicManager::run()
{
	PlayerObject* Leader = NULL;

	boolean running = true;

	while (running) {
		Position* characterPosition = character->getPosition();

		if (Leader != NULL) {
			Position* targetPos = Leader->getPosition();
			this->follow(Leader);
			this->characterLogic->runLogic();
		} else {
			Leader = ObjectManager::getInstance()->getPlayer(ABIGAIL_GUID);
			cout << "LogicManager: cant find leader named Abigail" << endl;
			if (Leader == NULL) {
				Leader = ObjectManager::getInstance()->getPlayer(SHINAIRI_GUID);
			}
			if (Leader == NULL) {
				cout << "LogicManager: cant find leader named Shinairi" << endl;
			}
		}

		Sleep(logicFrameRate);
	}
}

float LogicManager::findDirection(Position* characterPosition, Position* targetPosition) {
	float direction = 0.0f;

	int mainDirection = 0;

	float x1 = characterPosition->posX;
	float y1 = characterPosition->posY;

	float x2 = targetPosition->posX;
	float y2 = targetPosition->posY;

	char xMod = '=';
	char yMod = '=';

	float x3 = 0;
	float y3 = 0;

	if (x1 > x2) {
		xMod = '-';
		x3 = x1 - x2;
	}
	else if (x1 < x2) {
		xMod = '+';
		x3 = x2 - x1;
	}

	if (y1 > y2) {
		yMod = '-';
		y3 = y1 - y2;
	}
	else if (y1 < y2) {
		yMod = '+';
		y3 = y2 - y1;
	}

	float mod3 = 0.0f;

	if (xMod == '+' && yMod == '+' && x3 > y3) {
		mainDirection = 1;
		mod3 = y3 / x3 * pointDegree;
		direction = 0.0f + mod3;
	}
	else if (xMod == '+' && yMod == '+' && x3 < y3) {
		mainDirection = 2;
		mod3 = x3 / y3 * pointDegree;
		direction = 2 * pointDegree - mod3;
	}
	else if (xMod == '+' && yMod == '+' && x3 == y3) {
		mainDirection = 1122;
		direction = pointDegree;
	}

	else if (xMod == '-' && yMod == '+' && x3 > y3) {
		mainDirection = 4;
		mod3 = y3 / x3 * pointDegree;
		direction = 4 * pointDegree - mod3;
	}
	else if (xMod == '-' && yMod == '+' && x3 < y3) {
		mainDirection = 3;
		mod3 = x3 / y3 * pointDegree;
		direction = 2 * pointDegree + mod3;
	}
	else if (xMod == '-' && yMod == '+' && x3 == y3) {
		mainDirection = 3344;
		direction = 3 * pointDegree;
	}

	else if (xMod == '-' && yMod == '-' && x3 > y3) {
		mainDirection = 5;
		mod3 = y3 / x3 * pointDegree;
		direction = 4 * pointDegree + mod3;
	}
	else if (xMod == '-' && yMod == '-' && x3 < y3) {
		mainDirection = 6;
		mod3 = x3 / y3 * pointDegree;
		direction = 6 * pointDegree - mod3;
	}
	else if (xMod == '-' && yMod == '-' && x3 == y3) {
		mainDirection = 5566;
		direction = 5 * pointDegree;
	}

	else if (xMod == '+' && yMod == '-' && x3 > y3) {
		mainDirection = 8;
		mod3 = y3 / x3 * pointDegree;
		direction = 8 * pointDegree - mod3;
	}
	else if (xMod == '+' && yMod == '-' && x3 < y3) {
		mainDirection = 7;
		mod3 = x3 / y3 * pointDegree;
		direction = 6 * pointDegree + mod3;
	}
	else if (xMod == '+' && yMod == '-' && x3 == y3) {
		mainDirection = 7788;
		direction = 7 * pointDegree;
	}
	
	else if (xMod == '=' && yMod == '+') {
		mainDirection = 1111;
		direction = 2 * pointDegree;
	}
	else if (xMod == '=' && yMod == '-') {
		mainDirection = 3333;
		direction = 6 * pointDegree;
	}
	else if (xMod == '+' && yMod == '=') {
		mainDirection = 2222;
		direction = 0.0f;
	}
	else if (xMod == '-' && yMod == '=') {
		mainDirection = 4444;
		direction = 4 * pointDegree;
	}

	return direction;
}

float LogicManager::findRange(Position* characterPosition, Position* targetPosition) {
	int x1 = characterPosition->posX;
	int y1 = characterPosition->posY;
	int x2 = targetPosition->posX;
	int y2 = targetPosition->posY;

	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void LogicManager::follow(PlayerObject* target) {
	Position* characterPosition = character->getPosition();

	float requiredDirection = findDirection(characterPosition, target->getPosition());

	float rotationDifference = characterPosition->rotation > requiredDirection ? characterPosition->rotation - requiredDirection : requiredDirection - characterPosition->rotation;

	boolean isMovingLeft = false;
	if (rotationDifference > rotationDifferenceCheck) {
		if (characterPosition->rotation > requiredDirection) {
			ActionManager::getInstance()->stopAction(ActionType::MOVE_LEFT);
			ActionManager::getInstance()->startAction(ActionType::MOVE_RIGHT);
			isMovingLeft = false;
		}
		else if (characterPosition->rotation < requiredDirection && rotationDifference < 4 * pointDegree) {
			ActionManager::getInstance()->stopAction(ActionType::MOVE_RIGHT);
			ActionManager::getInstance()->startAction(ActionType::MOVE_LEFT);
			isMovingLeft = true;
		}
		else if (characterPosition->rotation < requiredDirection && rotationDifference > 4 * pointDegree) {
			ActionManager::getInstance()->stopAction(ActionType::MOVE_LEFT);
			ActionManager::getInstance()->startAction(ActionType::MOVE_RIGHT);
			isMovingLeft = false;
		}
		else {
			ActionManager::getInstance()->stopAction(ActionType::MOVE_RIGHT);
			ActionManager::getInstance()->startAction(ActionType::MOVE_LEFT);
			isMovingLeft = true;
		}
	}
	else {
		if (isMovingLeft == false) {
			ActionManager::getInstance()->stopAction(ActionType::MOVE_RIGHT);
		}
		else {
			ActionManager::getInstance()->stopAction(ActionType::MOVE_LEFT);
		}
	}

	if (findRange(character->getPosition(), target->getPosition()) > followMinRange) {
		ActionManager::getInstance()->startAction(ActionType::MOVE_FORWARD);
	}
	else {
		ActionManager::getInstance()->stopAction(ActionType::MOVE_FORWARD);
	}
}