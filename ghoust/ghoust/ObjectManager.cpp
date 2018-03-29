#include "stdafx.h"
#include "ObjectManager.h"
#include <iostream>

using namespace std;

ObjectManager* ObjectManager::objectManager = NULL;

ObjectManager::ObjectManager()
{
	this->memoryReader = MemoryReader::getInstance();
	this->baseAddress = memoryReader->readInt(Address::OBJECT_MANAGER);
	cout << "ObjectManager: Initializing - Base Address = " << &this->baseAddress << endl;
}

ObjectManager::~ObjectManager()
{
}

ObjectManager * ObjectManager::getInstance()
{
	if (objectManager == NULL) {
		objectManager = new ObjectManager();
		objectManager->setWowObjects();
	}

	return objectManager;
}

void ObjectManager::setWowObjects() {
	cout << "ObjectManager: Scanning for wow objects" << endl;

	int wowObject = this->memoryReader->readInt(this->baseAddress + Address::FIRST_OBJECT);
	int playerGuid = this->memoryReader->readInt(STATIC_POINTER::PLAYER_GUID);

	while (wowObject != 0 && (wowObject & 1) == 0)
	{
		if (playerGuid == this->memoryReader->readInt(wowObject + Address::OBJECT_GUID)) {
			this->player = new PlayerObject(wowObject);
		} else {
			this->createWowObject(wowObject);
		}

		int nextWowObject = this->memoryReader->readInt(wowObject + Address::NEXT_OBJECT);
		if (nextWowObject == wowObject) {
			break;
		} else {
			wowObject = nextWowObject;
		}
	}

	//cout << "ObjectManager: Scanned Player GUID: " << this->player->getGuid() << endl;
}

void ObjectManager::createWowObject(int objectBaseAddress) {
	int type = this->memoryReader->readInt(objectBaseAddress + Address::OBJECT_TYPE);

	long int guid = this->memoryReader->readInt(objectBaseAddress + Address::OBJECT_GUID);

	switch (type) {
		case 4:
			this->addPlayerObject(new PlayerObject(objectBaseAddress));
			break;
		default:
			break;
	}

	//cout << "ObjectManager::createWowObject type: " << type << " guid: " << guid << endl;
}


