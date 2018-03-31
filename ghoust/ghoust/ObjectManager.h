#pragma once

#include <map>
#include "WowObject.h"
#include "MemoryReader.h"
#include "PlayerObject.h"

using namespace std;

class ObjectManager {
	public:
		~ObjectManager();
		static ObjectManager* getInstance();

	private:
		ObjectManager();

	private:
		static ObjectManager* objectManager;
		MemoryReader* memoryReader;
		map<int, PlayerObject*> playerList;
		int baseAddress;
		PlayerObject* player;

	private:
		void setWowObjects();
		void createWowObject(int objectBaseAddress);

	public:
		void addPlayerObject(PlayerObject* playerObject) { this->playerList[playerObject->getGuid()] = playerObject; }
		PlayerObject* getPlayer() { return player;  }
		PlayerObject* getPlayer(int guid) { return playerList[guid]; }
};
