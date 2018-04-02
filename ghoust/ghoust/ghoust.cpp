#include "stdafx.h"

#include "LogicManager.h"
#include "Properties.h"

using namespace std;

int main() {
	Properties::botType = BotType::FOLLOWER;

	LogicManager* logicManager = LogicManager::getInstance();
	logicManager->run();
	getchar();
	return 0;
}