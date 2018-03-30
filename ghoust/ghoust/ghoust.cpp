#include "stdafx.h"

#include "LogicManager.h"
#include "Properties.h"

using namespace std;

int main() {
	Properties::playerClassType = ClassType::WARLOCK;

	LogicManager::getInstance();
	getchar();
	return 0;
}