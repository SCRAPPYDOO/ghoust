#include "stdafx.h"

#include "LogicManager.h"
#include "Properties.h"

using namespace std;

/**
    [0] BotType
    [1] Master
    [2] Window PID
*/
int main(string[] args) {
	Properties::botType = BotType::FOLLOWER;

	LogicManager* logicManager = LogicManager::getInstance();
	logicManager->run();
	getchar();
	return 0;
}
