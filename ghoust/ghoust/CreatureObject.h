#pragma once

#include "WowObject.h"

class Creatureobject : public WowObject {
	public :
		Creatureobject(int baseAddress) : WowObject(baseAddress) {}
		~Creatureobject() {}

	protected: 
		//static const int LevelOffset = 0x35 * 4;
		static const int CURRENT_HEALTH_OFFSET = 0x58;
		//static const int MaxHealthOffset = 0x1F * 4;
		//static const int CurrentManaOffset = 0x18 * 4;
		//static const int MaxManaOffset = 0x20 * 4;
		//static const int TargetGuidOffset = 0x12 * 4;

	public:
		int getCurrentHealth() { return getMemoryReader()->readInt(descriptorAddress + CURRENT_HEALTH_OFFSET); }
};