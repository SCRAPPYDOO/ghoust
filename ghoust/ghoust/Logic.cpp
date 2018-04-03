#include "stdafx.h"

#include "Logic.h"
#include "ObjectManager.h"

#include "MovementHelper.h"

#include <thread>
#include <chrono>

using namespace std;
using namespace std::chrono;

const float Logic::rotationDifferenceCheck = 0.16f;
const float Logic::rotationDifferenceToMove = 0.5f;

Logic::Logic() { 

	timers[TimerType::EAT_DRINK] = EAT_DRINK_TIMER;
	timers[TimerType::SCAN_WOW_OBJECTS] = SCAN_WOW_OBJECTS_TIMER;
}

Logic::~Logic()
{
}

void Logic::onLoop() {
	unsigned long framePerSecond = 33;
	unsigned long lastTimeSecond = ms.count();
	unsigned long frameTimer = framePerSecond;

	while (1) {
		milliseconds ms = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
		unsigned long currentTimeSecond = ms.count();
		unsigned long timeDiff = currentTimeSecond - lastTimeSecond;
		lastTimeSecond = currentTimeSecond;

		/*
		EAT TIMER
		*/
		if (logicState == LogicState::STATE_EAT_DRINK) {
			if (timers[TimerType::EAT_DRINK] < timeDiff) {
				changeLogicState(LogicState::STATE_NOTHING);
			}
			else {
				timers[TimerType::EAT_DRINK] -= timeDiff;
			};
		}

		if (timers[TimerType::SCAN_WOW_OBJECTS] < timeDiff) {
			ObjectManager::getInstance()->scanWowObjects();
			timers[TimerType::SCAN_WOW_OBJECTS] = SCAN_WOW_OBJECTS_TIMER;
		}
		else {
			timers[TimerType::SCAN_WOW_OBJECTS] -= timeDiff;
		};

		if (frameTimer < timeDiff) {
			frameTimer = framePerSecond;

			player = ObjectManager::getInstance()->getPlayer();

			if (player == NULL) {
				cout << "Logic: Player == NULL" << endl;
				continue;
			}

			Position* characterPosition = player->getPosition();

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

			/*
				COMBAT
			*/
			if (leader->isInCombat() || player->isInCombat()) {
				changeLogicState(LogicState::STATE_IN_COMBAT);

				if (player->getTarget() != 0 && player->getTarget() == leader->getTarget()) {
					NpcObject* playerTarget = ObjectManager::getInstance()->getCreatureObject(leader->getTarget());
					if (playerTarget != NULL && playerTarget->getCurrentHealth() > 0) {
						SpellId spellId = selectSpell(playerTarget);
						castSpell(spellId);
					}
				}

				//wybierz target leadera
				NpcObject* leaderTarget = ObjectManager::getInstance()->getCreatureObject(leader->getTarget());
				if (leaderTarget != NULL) {
					if (player->getTarget() != leader->getTarget()) {
						cout << "player target sie nie zgadzaja: " << endl;
						target(leaderTarget);
					}
				}
			}
			/*
				OUT OF COMBAT
			*/
			else {
				if (logicState == LogicState::STATE_IN_COMBAT) {
					changeLogicState(LogicState::STATE_NOTHING);
				}

				// If we are doing something skip
				if (logicState == LogicState::STATE_EAT_DRINK) {
					continue;
				}

				/*
					EAT
				*/
				eat();

				/*
					FOLLOW
				*/
				followLeader();

				/*
					SELF BUFFS
				*/
				buffPlayer();
			}	
		}
		else {
			frameTimer -= timeDiff;
		}
	}
}

void Logic::changeLogicState(LogicState newLogicState) {
	if (newLogicState != logicState && logicState == LogicState::STATE_EAT_DRINK) {
		cancelEat();
	}

	if (newLogicState != logicState && logicState == LogicState::STATE_MOVING) {
		cancelFollow();
	}

	logicState = newLogicState;
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
	float currentHealth = player->getCurrentHealth();
	float maxHealth = player->getMaxHealth();
	float percentOfhealth = currentHealth / maxHealth * 100.0f;

	float currentMana = player->getCurrentMana();
	float maxMana = player->getMaxMana();
	float percentOfMana = currentMana / maxMana * 100.0f;

	if (percentOfhealth < 30 || player->isManaUser() && percentOfMana < 30) {
		changeLogicState(LogicState::STATE_EAT_DRINK);
		if (percentOfhealth < 30) {
			cout << "Logic: Player need to eat " << percentOfhealth << "%" << endl;
			doAction(ActionType::EAT);
		}

		if (player->isManaUser() && percentOfMana < 30) {
			cout << "Logic: Player need to drink " << percentOfMana << "%" << endl;
			doAction(ActionType::DRINK);
		}
	}
}

void Logic::followLeader() {
	Position* characterPosition = player->getPosition();

	float requiredDirection = MovementHelper::findDirection(characterPosition, leader->getPosition());

	float rotationDifference = characterPosition->rotation > requiredDirection ? characterPosition->rotation - requiredDirection : requiredDirection - characterPosition->rotation;

	boolean isMovingLeft = false;
	if (rotationDifference > rotationDifferenceCheck) {
		changeLogicState(LogicState::STATE_MOVING);
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
		changeLogicState(LogicState::STATE_NOTHING);
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
	changeLogicState(LogicState::STATE_MOVING);
}

void Logic::stopFollow() {
	stopAction(ActionType::MOVE_FORWARD);
	changeLogicState(LogicState::STATE_NOTHING);
}

void Logic::cancelFollow() {
	doAction(ActionType::MOVE_FORWARD);
	doAction(ActionType::MOVE_LEFT);
	doAction(ActionType::MOVE_RIGHT);
	isMoving = false;
}

void Logic::cancelEat() {
	doAction(ActionType::JUMP);
	cout << "Logic: Stoping eat !";
}

bool Logic::target(NpcObject* target) {
	cout << "Logic: Targeting" << endl;
	bool targeting = true;
	bool foundTarget = false;
	while (targeting) {
		if (!leader->isInCombat() || !player->isInCombat()) {
			foundTarget = false;
			targeting = false;
			break;
		}
		if (target != NULL && target->getCurrentHealth() < 1) {
			cout << "Logic: My target is dead !?" << endl;
			foundTarget = false;
			targeting = false;
			break;
		}
		else {
			this->doActionNoSleep(ActionType::TARGET_NEAREST_ENEMY);
			if (target->getGuid() == player->getTarget()) {
				cout << "Logic: Found the target guid: " << player->getTarget() << endl;
				targeting = false;
				foundTarget = true;
				break;
			}
		}
	}

	return foundTarget;
}

void Logic::addFlag(LogicFlag logicFlag) {
    this->logicFlag |= logicFlag;
}

void Logic::removeFlag(LogicFlag logicFlag) {
    this->logicFlag &= ~logicFlag;
}

void Logic::hasFlag(LogicFlag logicFlag) {
    return (this->logicFlag & logicFlag) == logicFlag;
}
