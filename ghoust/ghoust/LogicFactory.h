#pragma once

#include "Logic.h"
#include "ClassType.h"
#include "WarlockLogic.h"
#include "Properties.h"
#include <string>

using namespace std;

class LogicFactory {
	public:
		static Logic* getLogic(PlayerObject * player) {
			Logic* selectedLogic = NULL;
			switch (Properties::playerClassType) {
				case WARLOCK:
					selectedLogic = new WarlockLogic(player);
					break;
				default:
					break;
			}
			
			string className = Properties::getPlayerClassTypeName();
			cout << "LogicFactory: loading " << className << " logic settings" << endl;

			return selectedLogic;
		}
};