#include "stdafx.h"

#include "LogicManager.h"
#include "LogicFactory.h"

#include <thread>
#include <chrono>

using namespace std;
using namespace std::chrono;

LogicManager* LogicManager::logicManager = NULL;

LogicManager* LogicManager::getInstance() {
	if(logicManager == NULL) {
		logicManager = new LogicManager();
	}

	return logicManager;
}

LogicManager::LogicManager() {
  cout << "LogicManager: Initializing" << endl;

}

LogicManager::~LogicManager()
{
}

void LogicManager::run()
{
	PlayerObject* character = ObjectManager::getInstance()->getPlayer();
	if (character != NULL) {
		characterLogic = LogicFactory::getLogic(character);

		this->characterLogic->onLoop();

	}
	else {
		cout << "LogicManager: Cant find  character !" << endl;
	}
}