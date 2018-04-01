#include "stdafx.h"

#include "Logic.h"
#include "ObjectManager.h"

#include "MovementHelper.h"

const float Logic::rotationDifferenceCheck = 0.16f;
const float Logic::rotationDifferenceToMove = 0.5f;

Logic::Logic(PlayerObject * player) { 
	this->player = player; 

	timers[EAT_DRINK_ACTION] = EAT_DRINK_TIMER;
}

Logic::~Logic()
{
}

void Logic::onLoop() {

	Position* characterPosition = player->getPosition();

	time_t currentTimeSecond = time(0);
	time_t timeDiff = currentTimeSecond - lastTimeSecond;
	lastTimeSecond = currentTimeSecond;

	if (timers[logicAction] < timeDiff) {
		ObjectManager::getInstance()->scanWowObjects();
		timers[logicAction] = SCAN_WOW_OBJECTS_TIMER;
	}
	else {
		timers[logicAction] -= timeDiff;
	};
	
    if(!player->isInCombat()) {
		/*
			EAT
		*/
        if (logicAction != NOTHING) {
            if (timers[logicAction] < timeDiff) {
                logicAction = NOTHING;
                timers[logicAction] = EAT_DRINK_TIMER;
                doAction(ActionType::JUMP);
                cout << "Logic: End of eating and drinking ! time to fight" << endl;
            }
            else {
                timers[logicAction] -= timeDiff;
                return;
            };
        }

		/*
			FOLLOW
		*/
		if (leader != NULL) {
			this->followLeader();
		}
		else {
			leader = ObjectManager::getInstance()->getPlayer(ABIGAIL_GUID);
			cout << "LogicManager: cant find leader named Abigail" << endl;
			if (leader == NULL) {
				leader = ObjectManager::getInstance()->getPlayer(SHINAIRI_GUID);
			}
			if (leader == NULL) {
				cout << "LogicManager: cant find leader named Shinairi" << endl;
			}
		}

        eat();
    } else {
		
    }

	/*
		Every Time
	*/
	buffPlayer();
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

void Logic::eat() {
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

void Logic::followLeader() {
	Position* characterPosition = player->getPosition();

	float requiredDirection = MovementHelper::findDirection(characterPosition, leader->getPosition());

	float rotationDifference = characterPosition->rotation > requiredDirection ? characterPosition->rotation - requiredDirection : requiredDirection - characterPosition->rotation;

	boolean isMovingLeft = false;
	if (rotationDifference > rotationDifferenceCheck) {
		if (characterPosition->rotation > requiredDirection) {
			ActionManager::getInstance()->stopAction(ActionType::MOVE_LEFT);
			ActionManager::getInstance()->startAction(ActionType::MOVE_RIGHT);
			isMovingLeft = false;
		}
		else if (characterPosition->rotation < requiredDirection && rotationDifference < 4 * MovementHelper::pointDegree) {
			ActionManager::getInstance()->stopAction(ActionType::MOVE_RIGHT);
			ActionManager::getInstance()->startAction(ActionType::MOVE_LEFT);
			isMovingLeft = true;
		}
		else if (characterPosition->rotation < requiredDirection && rotationDifference > 4 * MovementHelper::pointDegree) {
			ActionManager::getInstance()->stopAction(ActionType::MOVE_LEFT);
			ActionManager::getInstance()->startAction(ActionType::MOVE_RIGHT);
			isMovingLeft = false;
		}
		else {
			ActionManager::getInstance()->stopAction(ActionType::MOVE_RIGHT);
			ActionManager::getInstance()->startAction(ActionType::MOVE_LEFT);
			isMovingLeft = true;
		}
	}
	else {
		if (isMovingLeft == false) {
			ActionManager::getInstance()->stopAction(ActionType::MOVE_RIGHT);
		}
		else {
			ActionManager::getInstance()->stopAction(ActionType::MOVE_LEFT);
		}
	}

	float range = MovementHelper::findRange(player->getPosition(), leader->getPosition());

	if (range > startFollowRange) {
		ActionManager::getInstance()->startAction(ActionType::MOVE_FORWARD);
	}
	else if (range < stopFollowRange) {
		ActionManager::getInstance()->stopAction(ActionType::MOVE_FORWARD);
	}
}