#pragma once

#include "PlayerObject.h"
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

		Logic(PlayerObject * player);
		PlayerObject * player = NULL;
		PlayerObject * leader = NULL;

		long actionTimer = 0;
		time_t lastTimeSecond = 0;

		map<LogicAction, long> timers;

		LogicAction logicAction = NOTHING;

		void followLeader();

		void startAction(int actionType) { ActionManager::getInstance()->startAction(actionType); }
		void stopAction(int actionType) { ActionManager::getInstance()->stopAction(actionType); }
		void doAction(int actionType, int sleepTime);
		void doAction(int actionType);
		void castSpell(SpellId spellId);

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

	protected:
		virtual bool checkIfCanCastSpell(Spell* spell) = 0;
		virtual list<SpellId> getBuffList() = 0;
};

