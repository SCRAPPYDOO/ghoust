#include "stdafx.h"

#include "Logic.h"
#include "ObjectManager.h"

#include "MovementHelper.h"

const float Logic::rotationDifferenceCheck = 0.16f;
const float Logic::rotationDifferenceToMove = 0.5f;

Logic::Logic() { 

	timers[EAT_DRINK_ACTION] = EAT_DRINK_TIMER;
	timers[SCAN_WOW_OBJECTS] = SCAN_WOW_OBJECTS_TIMER;
}

Logic::~Logic()
{
}

void Logic::onLoop(long timeDiff) {
	player = ObjectManager::getInstance()->getPlayer();

	if (player == NULL) {
		cout << "Logic: Player == NULL";
		return;
	}

	Position* characterPosition = player->getPosition();

	if (timers[SCAN_WOW_OBJECTS] < timeDiff) {
		ObjectManager::getInstance()->scanWowObjects();
		timers[SCAN_WOW_OBJECTS] = SCAN_WOW_OBJECTS_TIMER;
	}
	else {
		timers[SCAN_WOW_OBJECTS] -= timeDiff;
		//cout << " SCAN_WOW_OBJECTS " << timers[SCAN_WOW_OBJECTS] << endl;
	};
	
	if (leader == NULL) {
		switch (player->getGuid()) {
			case CHARACTERS_GUID::KRONOS_III_GULLDAN_GUID:
				leader = ObjectManager::getInstance()->getPlayer(CHARACTERS_GUID::KRONOS_III_GHOUSTHUNTER_GUID);
				break;
			case CHARACTERS_GUID::ABIGAIL_GUID:
				leader = ObjectManager::getInstance()->getPlayer(CHARACTERS_GUID::SHINAIRI_GUID);
				break;
			case CHARACTERS_GUID::SHINAIRI_GUID:
				leader = ObjectManager::getInstance()->getPlayer(CHARACTERS_GUID::ABIGAIL_GUID);
				break;
			default:
				cout << "Logic: Invalid player guid" << endl;
				break;
		}
	
		if (leader == NULL) {
			cout << "Logic: cant find leader" << endl;
			return;
		}
	}

	if(leader->isInCombat() || player->isInCombat()) {
		if (isEating) {
			cancelEat();
		}
		if (isMoving) {
			cancelFollow();
		}
		cout << "player target: " << player->getTarget() << " leader target " << leader->getTarget() << endl;
		if (player->getTarget() != 0 && player->getTarget() == leader->getTarget()) {
			cout << "player leader target sie zgadza: " << endl;
			NpcObject* playerTarget = ObjectManager::getInstance()->getCreatureObject(leader->getTarget());
			if (playerTarget->getCurrentHealth() > 0) {
				SpellId spellId = selectSpell(playerTarget);
				castSpell(spellId);
			}
		}

		//wybierz target leadera
		NpcObject* leaderTarget = ObjectManager::getInstance()->getCreatureObject(leader->getTarget());
		if (leaderTarget != NULL) {
			cout << "player target: " << player->getTarget() << " leader target " << leader->getTarget() << endl;
			if (player->getTarget() != leader->getTarget()) {
				cout << "player target sie nie zgadzaja: " << endl;
				target(leaderTarget);
			}
		}
    } else {
		/*
		EAT TIMER
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
				cout << "Logic: Eating " << timers[logicAction] << endl;
				return;
			};
		}
		/*
		EAT
		*/
		eat();

		/*
		FOLLOW
		*/
		followLeader();
    }
	/*
		Every Time
	*/
	buffPlayer();
    
    cout << "Thread sleeping" << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}

void Logic::doAction(int actionType) {
	startAction(actionType);
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	stopAction(actionType);
}

void Logic::doActionNoSleep(int actionType) {
	startAction(actionType);
	stopAction(actionType);
}

void Logic::doAction(int actionType, int sleepTime) {
	startAction(actionType);
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	stopAction(actionType);
	std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
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
	
	if (player->isManaUser() && player->getMaxMana() - player->getCurrentMana() > 151) {
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
		startFollow();
	}
	else if (range < stopFollowRange) {
		stopFollow();
	}
}

void Logic::startFollow() {
	startAction(ActionType::MOVE_FORWARD);
	isMoving = true;
}

void Logic::stopFollow() {
	stopAction(ActionType::MOVE_FORWARD);
	isMoving = false;
}

void Logic::cancelFollow() {
	doAction(ActionType::MOVE_FORWARD);
	doAction(ActionType::MOVE_LEFT);
	doAction(ActionType::MOVE_RIGHT);
	isMoving = false;
}

void Logic::cancelEat() {
	isEating = false;
	logicAction = NOTHING;
	timers[logicAction] = EAT_DRINK_TIMER;
	doAction(ActionType::JUMP);
	cout << "Logic: Stoping eat !";
}

bool Logic::target(NpcObject* target) {
	bool targeting = true;
	cout << "Logic: Looking for target guid: " << target->getGuid() << endl;
	while (targeting) {
		if (target->getCurrentHealth() < 1) {
			cout << "Logic: My target is dead !?" << endl;
			return false;
		}
		else {
			this->doActionNoSleep(ActionType::TARGET_NEAREST_ENEMY);
			cout << "Logic: targeted guid: " << player->getTarget() << endl;
			if (target->getGuid() == player->getTarget()) {
				cout << "Logic: Found the target guid: " << player->getTarget() << endl;
				return true;
			}
		}
	}

	return false;
}
