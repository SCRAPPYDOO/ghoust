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
		bool running = true;
		characterLogic = LogicFactory::getLogic(character);
		long lastTimeSecond = 0;
		long loopTimer = 50; //logicFrameRate;

		while (running) {

			SYSTEMTIME st;

			GetSystemTime(&st);

			FILETIME  filetime;

			GetSystemTimeAsFileTime(&filetime);

			//cout << "LogicManager: filetime->dwHighDateTime " << filetime.dwHighDateTime << endl;
			//cout << "LogicManager: filetime->dwLowDateTime; " << filetime.dwLowDateTime << endl;
			long currentTimeSecond = filetime.dwLowDateTime;
			long timeDiff = currentTimeSecond - lastTimeSecond;
			lastTimeSecond = currentTimeSecond;

			//cout << "LogicManager: loopTimer " << loopTimer << " " << timeDiff << endl;

			if (loopTimer < timeDiff) {
				//cout << "LogicManager: Time " << st.wMinute << " " << st.wSecond << endl;
				this->characterLogic->onLoop(timeDiff);
				loopTimer = logicFrameRate;
			}
			else {
				loopTimer -= timeDiff;
			}
		}
	}
	else {
		cout << "LogicManager: Cant find  character !" << endl;
	}
}