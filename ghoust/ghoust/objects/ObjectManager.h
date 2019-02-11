#pragma once

#include <map>
#include "WowObject.h"
#include "MemoryReader.h"
#include "PlayerObject.h"
#include "NpcObject.h"

using namespace std;

class ObjectManager {
	public:
		~ObjectManager();
		static ObjectManager* getInstance();
		void scanWowObjects();

	private:
		ObjectManager();

	private:
		static ObjectManager* objectManager;
		MemoryReader* memoryReader;
		map<unsigned int, PlayerObject*> playerList;
		map<unsigned int, NpcObject*> npcList;
		int baseAddress;
		PlayerObject* player = NULL;

	private:
		void createWowObject(int objectBaseAddress);
		void addPlayerObject(PlayerObject* playerObject);
		void addNpcObject(NpcObject* npcObject);
		void scanForPlayer();

	public:
		PlayerObject* getPlayer() { return player;  }
		PlayerObject* getPlayer(unsigned int guid) { return playerList[guid]; }
		NpcObject* getCreatureObject(unsigned int guid) { return npcList[guid]; }
};
