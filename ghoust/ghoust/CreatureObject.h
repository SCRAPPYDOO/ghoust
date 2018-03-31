#pragma once

#include "WowObject.h"

class Creatureobject : public WowObject {
	public :
		Creatureobject(int baseAddress) : WowObject(baseAddress) {}
		~Creatureobject() {}

	protected: 

		/*
			DESCRIPTORS
		*/
		static const int CURRENT_HEALTH_OFFSET = 0x58;
		static const int MAX_HEALTH_OFFSET = 0x00000070;
		static const int CURRENT_MANA_OFFSET = 0x5C;
		static const int MAX_MANA_OFFSET = 0x00000074;
    
		static const int CURRENT_LEVEL_OFFSET = 0x88;
    
		static const int FIRST_BUFF_OFFSET = 0xBC;
		static const int FIRST_DEBUFF_OFFSET = 0x13C;
		static const int NEXT_BUFF_OFFSET = 0x4;
    
        static const int FLAGS_OFFSET = 0x000000B8;
        static const int FLAG_IS_IN_COMBAT = 0x80000;

	public:
		int getCurrentHealth() { return getMemoryReader()->readInt(descriptorAddress + CURRENT_HEALTH_OFFSET); }
		int getMaxHealth() { return getMemoryReader()->readInt(descriptorAddress + MAX_HEALTH_OFFSET); }
		int getCurrentMana() { return getMemoryReader()->readInt(descriptorAddress + CURRENT_MANA_OFFSET);  }
		int getMaxMana() { return getMemoryReader()->readInt(descriptorAddress + MAX_MANA_OFFSET); }
		int getCurrentLevel() { return getMemoryReader()->readInt(descriptorAddress + CURRENT_LEVEL_OFFSET); }
        int getFlags() { return getMemoryReader()->readInt(descriptorAddress + FLAGS_OFFSET); }
    
        bool isInCombat() { return hasFlag(FLAG_IS_IN_COMBAT) }
    
		bool hasBuff(int spellId) {
			int lastAddress;
			for (int i = 0; i<MAX_BUFF_SIZE; i++) {
				if (i == 0) {
					lastAddress = getMemoryReader()->readInt(descriptorAddress + FIRST_BUFF_OFFSET);
				}
				else {
					lastAddress = getMemoryReader()->readInt(lastAddress + NEXT_BUFF_OFFSET);
				}

				if (lastAddress == spellId) {
					return true;
				}
			}
			return false;
		}
    
        bool hasFlag(FlagType flagType) {
            return getFlags() & flagType;
        }
};
