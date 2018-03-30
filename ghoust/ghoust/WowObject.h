#pragma once

#include "MemoryReader.h"

using namespace std;

struct Position {
	float posX;
	float posY;
	float posZ;
	float rotation;
};

class WowObject {
	protected:
		static const int GUID_OFFSET = 0x30;
		static const int TYPE_OFFSET = 0x14;
		static const int X_POS_OFFSET = 0x9B8;
		static const int Y_POS_OFFSET = 0x9BC;
		static const int Z_POS_OFFSET = 0x9BC + 4;
		static const int ROTATION_OFFSET = 0x09C4;
		static const int DESCRIPTOR_OFFSET = 0x8;
		static const int FIRST_BUFF_OFFSET = 0xBC;
		static const int FIRST_DEBUFF_OFFSET = 0x13C;
		static const int NEXT_BUFF_OFFSET = 0x4;

	protected:
		int baseAddress;
		int descriptorAddress;

	public:
		WowObject(unsigned int baseAddress) { 
			this->baseAddress = baseAddress; 
			this->descriptorAddress = getDescriptorAddress();
		}
		~WowObject() {}

	public:
		int getBaseAddress() { return  this->baseAddress;  }
		int getGuid() { return getMemoryReader()->readInt(this->baseAddress + GUID_OFFSET); }
		int getDescriptorAddress() { return getMemoryReader()->readInt(this->baseAddress + DESCRIPTOR_OFFSET); }
		int getType() { return getMemoryReader()->readInt(this->baseAddress + TYPE_OFFSET); }

		Position* getPosition() {
			Position* position = new Position();
			position->posX = getMemoryReader()->readFloat(this->baseAddress + X_POS_OFFSET);
			position->posY = getMemoryReader()->readFloat(this->baseAddress + Y_POS_OFFSET);
			position->posZ = getMemoryReader()->readFloat(this->baseAddress + Z_POS_OFFSET);
			position->rotation = getMemoryReader()->readFloat(this->baseAddress + ROTATION_OFFSET);

			return position;
		}

		bool hasBuff(int spellId) {
			int firstBuff = getMemoryReader()->readInt(this->baseAddress + FIRST_BUFF_OFFSET);
			cout << " first buff " << firstBuff << " adress: " << &firstBuff << endl;
			return false;
		}
	protected:
		MemoryReader * getMemoryReader() { return MemoryReader::getInstance(); }
};