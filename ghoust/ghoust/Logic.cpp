#include "stdafx.h"

#include "Logic.h"

Logic::Logic(PlayerObject * player) { 
	this->player = player; 

	timers[EAT_DRINK_ACTION] = EAT_TIMER_SECONDS;
}

Logic::~Logic()
{
}

void Logic::runLogic() {

	time_t currentTimeSecond = time(0);
	time_t timeDiff = currentTimeSecond - lastTimeSecond;
	lastTimeSecond = currentTimeSecond;

    if(!player->isInCombat()) {
        if (logicAction != NOTHING) {
            if (timers[logicAction] < timeDiff) {
                logicAction = NOTHING;
                timers[logicAction] = EAT_TIMER_SECONDS;
                doAction(ActionType::JUMP);
                cout << "Logic: End of eating and drinking ! time to fight" << endl;
            }
            else {
                timers[logicAction] -= timeDiff;
                return;
            };
        }

        // if combat  do not  eat ,  if  eating and start combat stop eat  fight
        eat(timeDiff);
    } else {
        //scan
        
        
        
        buffPlayer();
    }
}

void Logic::doAction(int actionType) {
	startAction(actionType);
	Sleep(50);
	stopAction(actionType);
}

void Logic::doAction(int actionType, int sleepTime) {
	startAction(actionType);
	Sleep(50);
	stopAction(actionType);
	Sleep(sleepTime);
}

void Logic::buffPlayer() {
	list <SpellId> ::iterator it;
	list <SpellId> availableBuffs = getBuffList();
	for (it = availableBuffs.begin(); it != availableBuffs.end(); ++it) {
		if (!player->hasBuff(*it)) {
			cout << "Logic: Player dont have buff id: " << *it << endl;
			castSpell(*it);
		}
	}
}

void Logic::castSpell(SpellId spellId) {
	Spell* spell = getSpellById(spellId);
	if (player->getCurrentMana() > spell->manaCost) {
		if (checkIfCanCastSpell(spell)) {
			doAction(spell->actionBind, spell->castTime);
		}
	}
}

void Logic::eat(time_t timeDiff) {
	if (player->getMaxHealth() - player->getCurrentHealth() > 61) {
		logicAction = EAT_DRINK_ACTION;
		cout << "Logic: Player need to eat" << endl;
		doAction(ActionType::EAT);
	}

	if (player->getMaxMana() - player->getCurrentMana() > 151) {
		logicAction = EAT_DRINK_ACTION;
		cout << "Logic: Player need to drink" << endl;
		doAction(ActionType::DRINK);
	}
}
