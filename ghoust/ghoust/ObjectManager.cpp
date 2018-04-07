#include "stdafx.h"

#include "ObjectManager.h"
#include "ObjectType.h"

#include <iostream>

using namespace std;

ObjectManager* ObjectManager::objectManager = NULL;

ObjectManager::ObjectManager()
{
	this->memoryReader = MemoryReader::getInstance();
	this->baseAddress = memoryReader->readInt(Address::OBJECT_MANAGER);
	cout << "ObjectManager: Initializing - ObjectManager Base Address = " << &this->baseAddress << endl;
}

ObjectManager::~ObjectManager()
{
}

ObjectManager * ObjectManager::getInstance()
{
	if (objectManager == NULL) {
		objectManager = new ObjectManager();
		objectManager->scanForPlayer();
		objectManager->scanWowObjects();
	}

	return objectManager;
}

void ObjectManager::scanForPlayer() {
	int firstObject = this->memoryReader->readInt(this->baseAddress + Address::FIRST_OBJECT);
	unsigned int playerGuid = this->memoryReader->readInt(STATIC_POINTER::PLAYER_GUID);

	while (firstObject != 0 && (firstObject & 1) == 0)
	{
		if (playerGuid == this->memoryReader->readUnsignedInt(firstObject + Address::OBJECT_GUID)) {
			this->player = new PlayerObject(firstObject);
			cout << "Player base address: " << firstObject << " pointer " << &firstObject << endl;
			return;
		}

		int nextWowObject = this->memoryReader->readInt(firstObject + Address::NEXT_OBJECT);
		if (nextWowObject == firstObject) {
			break;
		}
		else {
			firstObject = nextWowObject;
		}
	}
}

void ObjectManager::scanWowObjects() {
	//cout << "ObjectManager: Scanning for wow objects" << endl;

	/*
		Clear lists
	*/
	this->playerList.clear();
	this->npcList.clear();

	int firstObject = this->memoryReader->readInt(this->baseAddress + Address::FIRST_OBJECT);

	while (firstObject != 0 && (firstObject & 1) == 0)
	{
		this->createWowObject(firstObject);

		int nextWowObject = this->memoryReader->readInt(firstObject + Address::NEXT_OBJECT);
		if (nextWowObject == firstObject) {
			break;
		} else {
			firstObject = nextWowObject;
		}
	}
}

void ObjectManager::createWowObject(int objectBaseAddress) {
	int type = this->memoryReader->readInt(objectBaseAddress + Address::OBJECT_TYPE);

	switch (type) {
		case ObjectType::PLAYER:
			this->addPlayerObject(new PlayerObject(objectBaseAddress));
			break;
		case ObjectType::UNIT:
			this->addNpcObject(new NpcObject(objectBaseAddress));
			break;
		default:
			break;
	}
}

void ObjectManager::addPlayerObject(PlayerObject* playerObject) { 
	this->playerList[playerObject->getGuid()] = playerObject; 
}

void ObjectManager::addNpcObject(NpcObject* npcObject) {
	this->npcList[npcObject->getGuid()] = npcObject;
}


