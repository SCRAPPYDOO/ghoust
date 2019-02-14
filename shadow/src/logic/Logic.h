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

enum LogicType {
	LOGIC_BOT,
	LOGIC_FOLLOWER,
};

enum LogicFlag {
	FLAG_NOTHING = 0x1,
	FLAG_IN_COMBAT = 0x2,
	FLAG_MOVING = 0x4,
	FLAG_ROTATING = 0x8,
	FLAG_EAT_DRINK = 0x10,
	FLAG_TARGETING = 0x20,
};

enum TimerType {
	EAT_DRINK,
	SCAN_WOW_OBJECTS,
	JUMP,
};

class Logic
{
	public:
		void onLoop();

		~Logic();

	protected:
		static const int SPELL_RANGE = 30;
		static const int  WAYPOINT_RANGE = 5;
		static const int startFollowRange = 8;
		static const int stopFollowRange = 5;
		static const float rotationDifferenceCheck;
		static const float rotationDifferenceToMove;

		Logic();

		PlayerObject * leader = NULL;
		PlayerObject * player = NULL;
		NpcObject* playerTarget = NULL;

		/*
			WAYPOINTS
		*/
		static map<int, Position*> waypoints;
		Position* nextWaypoint = NULL;
		int waypointNumber = 1;
		int direction = 0;

		LogicType logicType = LogicType::LOGIC_BOT;
		bool isBot() {
			return logicType == LogicType::LOGIC_BOT;
		}
		bool isFollower() {
			return logicType == LogicType::LOGIC_FOLLOWER;
		}

		map<TimerType, unsigned long> timers;

        int logicFlag = LogicFlag::FLAG_NOTHING;

		void startAction(int actionType) { ActionManager::getInstance()->startAction(actionType); }
		void stopAction(int actionType) { ActionManager::getInstance()->stopAction(actionType); }
		void doAction(int actionType, int sleepTime);
		void doAction(int actionType);
		void doActionNoSleep(int actionType);
		void castSpell(SpellId spellId);

		/*
			COMBAT
		*/
		bool target(NpcObject* target);
		bool targetAttacker();
		bool targetRandomTarget();
		
		/*
			CHANGE LOGIC STATE
		*/
        void addFlag(LogicFlag logicFlag);
        void removeFlag(LogicFlag logicFlag);
        bool hasFlag(LogicFlag logicFlag);
		
		/*
			MOVEMENT
		*/
		bool isInRange(Position* position);
		bool isInRange(CreatureObject* target);
		void followLeader();
		bool faceTarget(CreatureObject* target);
		bool facePosition(Position* position);
		void startMove();
		void stopMove();
		void cancelMove();
		void cancelRotate();

		/*
			BUFFS
		*/
		void buffParty();
		void buffTarget(PlayerObject* target);
		void buffPlayer();

		/*
			EAT DRINK
		*/
		bool eat();
		void cancelEat();

	protected:
		virtual bool checkIfCanCastSpell(Spell* spell) = 0; // Any Logic for player to check if  he can cast selected spell
		virtual list<SpellId> getBuffList() = 0;			// List of buffs available for player
		virtual SpellId selectSpell(CreatureObject* target) = 0; // logic to select spell to cast on enemy
};

