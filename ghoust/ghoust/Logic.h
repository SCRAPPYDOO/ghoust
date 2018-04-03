#pragma once

#include "PlayerObject.h"
#include "NpcObject.h"
#include "ActionManager.h"
#include "SpellDefinition.h"
#include "Properties.h"
#include "Utils.h"

#include <list>
#include <iterator>
#include <map>
#include <ctime>

using namespace std;

using namespace std;

enum LogicState {
	STATE_NOTHING = 0x1,
	STATE_IN_COMBAT = 0x2,
	STATE_MOVING = 0x4,
	STATE_ROTATING = 0x8,
	STATE_EAT_DRINK = 0x16,
};

enum TimerType {
	EAT_DRINK,
	SCAN_WOW_OBJECTS,
};

class Logic
{
	public:
		void onLoop();

		~Logic();

	protected:
		static const int startFollowRange = 8;
		static const int stopFollowRange = 5;
		static const float rotationDifferenceCheck;
		static const float rotationDifferenceToMove;

		Logic();

		PlayerObject * leader = NULL;
		PlayerObject * player = NULL;

		bool isMoving = false;

		long actionTimer = 0;

		map<TimerType, unsigned long> timers;

		LogicState logicState = STATE_NOTHING;
        int logicFlag = LogicState::STATE_NOTHING;

		void followLeader();

		void startAction(int actionType) { ActionManager::getInstance()->startAction(actionType); }
		void stopAction(int actionType) { ActionManager::getInstance()->stopAction(actionType); }
		void doAction(int actionType, int sleepTime);
		void doAction(int actionType);
		void doActionNoSleep(int actionType);
		void castSpell(SpellId spellId);

		bool target(NpcObject* target);

		/*
			CHANGE LOGIC STATE
		*/
		void changeLogicState(LogicState newLogicState);
        void addFlag(LogicState logicFlag);
        void removeFlag(LogicState logicFlag);
        void hasFlag(LogicState logicFlag);
		
		/*
			MOVEMENT
		*/
		void startFollow();
		void stopFollow();
		void cancelFollow();

		/*
			BUFFS
		*/
		void buffParty();
		void buffTarget(PlayerObject* target);
		void buffPlayer();

		/*
			EAT DRINK
		*/
		void eat();
		void cancelEat();

	protected:
		virtual bool checkIfCanCastSpell(Spell* spell) = 0; // Any Logic for player to check if  he can cast selected spell
		virtual list<SpellId> getBuffList() = 0;			// List of buffs available for player
		virtual SpellId selectSpell(CreatureObject* target) = 0; // logic to select spell to cast on enemy
};

