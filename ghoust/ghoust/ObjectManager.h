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
		map<int, PlayerObject*> playerList;
		map<int, NpcObject*> npcList;
		int baseAddress;
		PlayerObject* player;

	private:
		void createWowObject(int objectBaseAddress);
		void addPlayerObject(PlayerObject* playerObject);
		void addNpcObject(NpcObject* npcObject);

	public:
		PlayerObject* getPlayer() { return player;  }
		PlayerObject* getPlayer(int guid) { return playerList[guid]; }
};
