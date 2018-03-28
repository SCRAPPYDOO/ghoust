#include "stdafx.h"
#include "LogicManager.h"

LogicManager* LogicManager::logicManager = NULL;

LogicManager* LogicManager::getInstance() {
	if(this->logicManager == NULL) {
		logicManager = new LogicManager();
	}

	return this->logicManager;
}

LogicManager::LogicManager() {
  cout << "LogicManager: Initializing" << endl;

  runFollowingThread();
}

LogicManager::~LogicManager()
{
}

LogicManager::runFollowingThread() {
  //30 razy na sekunde ?
  PlayerObject* player = ObjectManager::getInstance()->getPlayer();
  PlayerObject* target = ObjectManager::getInstance()->getTarget(CHARACTERS_GUID::ABIGAIL_GUID);

  int distance = calculateDistance();
  float rotation = calculateRotation();



  if(distance > 10) {
    if(checkRotation()) {
      follow()

    } else {
      rotate()
    }
  }
}
