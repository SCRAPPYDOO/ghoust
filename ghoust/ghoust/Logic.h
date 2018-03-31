#pragma once

#include "PlayerObject.h"
#include "ActionManager.h"
#include "SpellType.h"
#include <list>
#include <iterator>


using namespace std;

class Logic
{
	public:
		Logic(PlayerObject * player) { this->player = player;  }
		virtual void runLogic() = 0;
	protected:
		PlayerObject * player;
		list<SpellType> classBuffList;
		void buff() {
			list <SpellType> ::iterator it;
			for (it = classBuffList.begin(); it != classBuffList.end(); ++it) {
				if (!player->hasBuff(*it)) {
					ActionManager::getInstance()->startAction(WarlockActionType::CAST_DEMON_SKIN);
					Sleep(50);
					ActionManager::getInstance()->stopAction(WarlockActionType::CAST_DEMON_SKIN);
				}
			}
		}

};

