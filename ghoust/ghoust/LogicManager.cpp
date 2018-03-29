#include "stdafx.h"
#include "LogicManager.h"
#include "ActionManager.h"
#include <thread>

using namespace std;

LogicManager* LogicManager::logicManager = NULL;
const float LogicManager::degree = 0.01745325f;
const float LogicManager::pointDegree = 0.78f;

LogicManager* LogicManager::getInstance() {
	if(logicManager == NULL) {
		logicManager = new LogicManager();
	}

	return logicManager;
}

LogicManager::LogicManager() {
  cout << "LogicManager: Initializing" << endl;
  run();
}

LogicManager::~LogicManager()
{
}

void LogicManager::getPosition()
{
	PlayerObject* target = NULL;
	boolean running = true;
	while (running) {
		Position* pos = ObjectManager::getInstance()->getPlayer()->getPosition();

		cout << "Player position: posX: " << pos->posX << " posY: " << pos->posY << " posZ: " << pos->posZ << " rotation " << pos->rotation << endl;

		cout << "Player Health = " << ObjectManager::getInstance()->getPlayer()->getCurrentHealth() << endl;

		
		if (target != NULL) {
			cout << "Target: Health = " << target->getCurrentHealth() << endl;

			Position* targetPos = target->getPosition();

			cout << "Target position: posX: " << targetPos->posX << " posY: " << targetPos->posY << " posZ: " << targetPos->posZ << " rotation " << targetPos->rotation << endl;
		}
		else {
			target = ObjectManager::getInstance()->getPlayer(ABIGAIL_GUID);
			cout << "Target: Nie moge znalezc Abigail" << endl;
			if (target == NULL) {
				target = ObjectManager::getInstance()->getPlayer(SHINAIRI_GUID);
			}
			if (target == NULL) {
				cout << "Target: Nie moge znalezc Shinairi" << endl;
			}
		}

		float requiredDirection = findDirection(target);

		float roznica = pos->rotation > requiredDirection ? pos->rotation - requiredDirection : requiredDirection - pos->rotation;
		cout << " roznica: " << roznica << " moja rot " << pos->rotation << " required " << requiredDirection << endl;
		if (roznica > 0.20f) {
			//if (roznica > 4 * pointDegree) {
				ActionManager::getInstance()->startAction(ActionType::MOVE_RIGHT);
			//}
			/*else {
				ActionManager::getInstance()->startAction(ActionType::MOVE_LEFT);
				Sleep(50);
				ActionManager::getInstance()->stopAction(ActionType::MOVE_LEFT);
			}*/
		}
		else {
			ActionManager::getInstance()->stopAction(ActionType::MOVE_RIGHT);
		}


		std::this_thread::sleep_for(std::chrono::milliseconds(33));
		system("cls");
	}
}

void LogicManager::run() {
	cout << "LogicManager: starting thread" << endl;
	getPosition();
	//thread t1(&LogicManager::getPosition, this);
  //30 razy na sekunde ?
  /*PlayerObject* player = ObjectManager::getInstance()->getPlayer();
  PlayerObject* target = ObjectManager::getInstance()->getTarget(CHARACTERS_GUID::ABIGAIL_GUID);

  int distance = calculateDistance();
  float rotation = calculateRotation();



  if(distance > 10) {
    if(checkRotation()) {
      follow()

    } else {
      rotate()
    }
  }*/
}

float LogicManager::findDirection(PlayerObject* target) {
	float direction = 0.0f;
	if (target != NULL) {
		Position* myPosition = ObjectManager::getInstance()->getPlayer()->getPosition();
		Position* targetPosition = target->getPosition();

		int mainDirection = 0;

		float x1 = myPosition->posX;
		float y1 = myPosition->posY;

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
	}
	return direction;
}

