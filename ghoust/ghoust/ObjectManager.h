#pragma once

#include <map>
#include "WowObject.h"
#include "MemoryReader.h"
#include "PlayerObject.h"

class ObjectManager {
	public:
		~ObjectManager();
		static ObjectManager* getInstance();

	private:
		ObjectManager();

	private:
		static ObjectManager* objectManager;
		MemoryReader* memoryReader;
		std::map<int, PlayerObject*> playerList;
		int baseAddress;
		PlayerObject* player;

	private:
		void setWowObjects();
		void createWowObject(int objectBaseAddress);

	public:
		void addPlayerObject(PlayerObject* playerObject);
		PlayerObject* getPlayer();
		PlayerObject* getTarget(int guid);
};
