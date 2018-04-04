#include "stdafx.h"

#include "Logic.h"
#include "ObjectManager.h"
#include "Logger.h"
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
	milliseconds ms = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
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
		if (hasFlag(LogicFlag::FLAG_EAT_DRINK)) {
			if (timers[TimerType::EAT_DRINK] < timeDiff) {
				cancelEat();
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
				addFlag(LogicFlag::FLAG_IN_COMBAT);

				if (leader->getTarget() != 0) {
					NpcObject* leaderTarget = ObjectManager::getInstance()->getCreatureObject(leader->getTarget());
					if (leaderTarget != NULL) {
						/*
							TARGETING
						*/
						if (player->getTarget() != leader->getTarget()) {
							target(leaderTarget);
						}
						
						/*
							FACING TARGET
						*/
						if (!faceTarget(leaderTarget)) {
							continue;
						}

						/*
							CASTING SPELL
						*/
						if (player->getTarget() == leader->getTarget() && leaderTarget->getCurrentHealth() > 0) {
							SpellId spellId = selectSpell(leaderTarget);
							castSpell(spellId);
						}
					}
				}
			}
			/*
				OUT OF COMBAT
			*/
			else {
				if (hasFlag(LogicFlag::FLAG_IN_COMBAT)) {
					removeFlag(LogicFlag::FLAG_IN_COMBAT);
				}

				// If we are doing something skip
				if (hasFlag(LogicFlag::FLAG_EAT_DRINK)) {
					continue;
				}

				/*
					EAT
				*/
				if (!hasFlag(LogicFlag::FLAG_EAT_DRINK) && eat()) {
					continue;
				}

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

void Logic::doAction(int actionType) {
	startAction(actionType);
	//std::this_thread::sleep_for(std::chrono::milliseconds(50));
	stopAction(actionType);
}

void Logic::doActionNoSleep(int actionType) {
	startAction(actionType);
	stopAction(actionType);
}

void Logic::doAction(int actionType, int sleepTime) {
	startAction(actionType);
	//std::this_thread::sleep_for(std::chrono::milliseconds(50));
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
	if (spell == NULL) {
		cout << "Logic castSpell(spellId): Cant find spell id: " << spellId << endl;
		return;
	}
	if (player->getCurrentMana() > spell->manaCost) {
		if (checkIfCanCastSpell(spell)) {
			doAction(spell->actionBind, spell->castTime);
		}
	}
}

bool Logic::eat() {
	float currentHealth = player->getCurrentHealth();
	float maxHealth = player->getMaxHealth();
	float percentOfhealth = currentHealth / maxHealth * 100.0f;

	float currentMana = player->getCurrentMana();
	float maxMana = player->getMaxMana();
	float percentOfMana = currentMana / maxMana * 100.0f;

	if (percentOfhealth < 30 || player->isManaUser() && percentOfMana < 30) {
		addFlag(LogicFlag::FLAG_EAT_DRINK);
		if (percentOfhealth < 30) {
			cout << "Logic: Player need to eat " << percentOfhealth << "%" << endl;
			doAction(ActionType::EAT);
		}

		if (player->isManaUser() && percentOfMana < 30) {
			cout << "Logic: Player need to drink " << percentOfMana << "%" << endl;
			doAction(ActionType::DRINK);
		}
		return true;
	}
	return false;
}

bool Logic::faceTarget(CreatureObject* target) {
	Position* characterPosition = player->getPosition();

	float requiredDirection = MovementHelper::findDirection(characterPosition, target->getPosition());

	float rotationDifference = characterPosition->rotation > requiredDirection ? characterPosition->rotation - requiredDirection : requiredDirection - characterPosition->rotation;

	boolean isMovingLeft = false;
	if (rotationDifference > rotationDifferenceCheck) {
		addFlag(LogicFlag::FLAG_ROTATING);
		stopFollow();
		if (characterPosition->rotation > requiredDirection) {
			ActionManager::getInstance()->stopAction(ActionType::MOVE_LEFT);
			ActionManager::getInstance()->startAction(ActionType::MOVE_RIGHT);
			isMovingLeft = false;
		}
		else if (characterPosition->rotation < requiredDirection && rotationDifference < 4 * MovementHelper::pointDegree - 0.30) {
			ActionManager::getInstance()->stopAction(ActionType::MOVE_RIGHT);
			ActionManager::getInstance()->startAction(ActionType::MOVE_LEFT);
			isMovingLeft = true;
		}
		else if (characterPosition->rotation < requiredDirection && rotationDifference > 4 * MovementHelper::pointDegree - 0.30) {
			ActionManager::getInstance()->stopAction(ActionType::MOVE_LEFT);
			ActionManager::getInstance()->startAction(ActionType::MOVE_RIGHT);
			isMovingLeft = false;
		}
		else {
			ActionManager::getInstance()->stopAction(ActionType::MOVE_RIGHT);
			ActionManager::getInstance()->startAction(ActionType::MOVE_LEFT);
			isMovingLeft = true;
		}

		return false;
	}
	else {
		removeFlag(LogicFlag::FLAG_ROTATING);
		doActionNoSleep(ActionType::MOVE_RIGHT);
		doActionNoSleep(ActionType::MOVE_LEFT);

		return true;
	}
}

void Logic::followLeader() {
	Position* characterPosition = player->getPosition();

	faceTarget(leader);

	float range = MovementHelper::findRange(player->getPosition(), leader->getPosition());

	if (!hasFlag(LogicFlag::FLAG_ROTATING) && range > startFollowRange) {
		startFollow();
	}
}

void Logic::startFollow() {
	startAction(ActionType::MOVE_FORWARD);
	addFlag(LogicFlag::FLAG_MOVING);
}

void Logic::stopFollow() {
	stopAction(ActionType::MOVE_FORWARD);
	removeFlag(LogicFlag::FLAG_MOVING);
}

void Logic::cancelMove() {
	doAction(ActionType::MOVE_FORWARD);
	removeFlag(LogicFlag::FLAG_MOVING);
}

void Logic::cancelRotate() {
	doAction(ActionType::MOVE_LEFT);
	doAction(ActionType::MOVE_RIGHT);
	removeFlag(LogicFlag::FLAG_ROTATING);
}

void Logic::cancelEat() {
	doAction(ActionType::JUMP);
	removeFlag(LogicFlag::FLAG_EAT_DRINK);
	cout << "Logic: Stoping eat !";
}

bool Logic::target(NpcObject* target) {
	if (!leader->isInCombat()) {
		Logger::log("Logic: Leader is not in combat anymore, stopping targeting.");
		return false;
	}
	if (target != NULL && target->getCurrentHealth() < 1) {
		cout << "Logic: My target is dead !?" << endl;
		return false;;
	}
	else {
		this->doActionNoSleep(ActionType::TARGET_NEAREST_ENEMY);
		if (target->getGuid() == player->getTarget()) {
			cout << "Logic: Found the target guid: " << player->getTarget() << endl;
			return true;
		}
		return false;
	}

	return false;
}

void Logic::addFlag(LogicFlag logicFlag) {
	if (logicFlag == LogicFlag::FLAG_IN_COMBAT || logicFlag == LogicFlag::FLAG_EAT_DRINK) {
		if (logicFlag != LogicFlag::FLAG_EAT_DRINK && hasFlag(LogicFlag::FLAG_EAT_DRINK)) {
			cout << "Logic: Attempt to remove FLAG_EAT_DRINK" << endl;
			cancelEat();
		}

		if (logicFlag != LogicFlag::FLAG_MOVING && hasFlag(LogicFlag::FLAG_MOVING)) {
			cout << "Logic: Attempt to remove FLAG_MOVING" << endl;
			cancelMove();
		}

		if (!hasFlag(LogicFlag::FLAG_TARGETING) && logicFlag != LogicFlag::FLAG_ROTATING && hasFlag(LogicFlag::FLAG_ROTATING)) {
			cout << "Logic: Attempt to remove FLAG_ROTATING" << endl;
			cancelRotate();
		}
	}

	if (!hasFlag(logicFlag)) {
		this->logicFlag |= logicFlag;
		cout << "Logic: Add flag " << logicFlag << endl;
	}
}

void Logic::removeFlag(LogicFlag logicFlag) {
	bool hasFlag = this->hasFlag(LogicFlag::FLAG_IN_COMBAT);
	if (this->hasFlag(logicFlag)) {
		cout << "Logic: Remove flag " << logicFlag  << endl;
		this->logicFlag &= ~logicFlag;
	}
}

bool Logic::hasFlag(LogicFlag logicFlag) {
	return this->logicFlag & logicFlag;
}
