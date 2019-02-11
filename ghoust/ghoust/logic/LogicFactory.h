#pragma once

#include "Logic.h"
#include "ClassType.h"
#include "class/warlock/WarlockLogic.h"
#include "Properties.h"
#include <string>

using namespace std;

class LogicFactory {
	public:
		static Logic* getLogic(PlayerObject * player) {
			Logic* selectedLogic = NULL;

			switch (player->getClass()) {
				case WARLOCK:
					selectedLogic = new WarlockLogic();
					break;
				default:
					break;
			}
			
			string className = Properties::getClassTypeName(player->getClass());
			cout << "LogicFactory: loading " << className << " logic settings" << endl;

			return selectedLogic;
		}
};
