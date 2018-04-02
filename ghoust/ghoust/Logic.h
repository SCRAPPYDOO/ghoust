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

enum LogicAction {
	NOTHING,
	EAT_DRINK_ACTION,
	SCAN_WOW_OBJECTS,
};

class Logic
{
	public:
		void onLoop(long timeDiff);

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
		bool isEating = false;

		long actionTimer = 0;

		map<LogicAction, long> timers;

		LogicAction logicAction = NOTHING;

		void followLeader();

		void startAction(int actionType) { ActionManager::getInstance()->startAction(actionType); }
		void stopAction(int actionType) { ActionManager::getInstance()->stopAction(actionType); }
		void doAction(int actionType, int sleepTime);
		void doAction(int actionType);
		void doActionNoSleep(int actionType);
		void castSpell(SpellId spellId);

		bool target(NpcObject* target);

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
		virtual SpellId selectSpell(NpcObject* target) = 0; // logic to select spell to cast on enemy
};

