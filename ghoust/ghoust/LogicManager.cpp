#include "stdafx.h"

#include "LogicManager.h"
#include "LogicFactory.h"

#include <thread>

using namespace std;

LogicManager* LogicManager::logicManager = NULL;

const float LogicManager::logicFrameRate = 17;

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
	boolean running = true;

	while (running) {
		this->characterLogic->onLoop();

		Sleep(logicFrameRate);
	}
}