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
		static const int FIRST_BUFF_OFFSET = 0xBC;
		static const int FIRST_DEBUFF_OFFSET = 0x13C;
		static const int NEXT_BUFF_OFFSET = 0x4;

	public:
		int getCurrentHealth() { return getMemoryReader()->readInt(descriptorAddress + CURRENT_HEALTH_OFFSET); }

		bool hasBuff(int spellId) {
			int lastAddress;
			for (int i = 0; i<MAX_BUFF_SIZE; i++) {
				if (i == 0) {
					lastAddress = getMemoryReader()->readInt(descriptorAddress + FIRST_BUFF_OFFSET);
				}
				else {
					lastAddress = getMemoryReader()->readInt(lastAddress + NEXT_BUFF_OFFSET);
				}
				cout << " first buff " << lastAddress << " adress: " << &lastAddress << endl;
				if (lastAddress == spellId) {
					return true;
				}
			}
			return false;
		}
};