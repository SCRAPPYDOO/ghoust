#pragma once

#include "MemoryReader.h"

struct Position {
	float posX;
	float posY;
	float posZ;
	float rotation;
};

class WowObject {
	protected:
		static const int GUID_OFFSET = 0x30;
		static const int NEXT_OBJECT_OFFSET = 0x3C;
		static const int TYPE_OFFSET = 0x14;
		static const int X_POS_OFFSET = 0x9B8;
		static const int Y_POS_OFFSET = 0x9BC;
		static const int Z_POS_OFFSET = 0x9BC + 4;
		static const int ROTATION_OFFSET = 0x09C4;
		static const int DESCRIPTOR_OFFSET = 0x8;

	protected:
		int baseAddress;
		int descriptorAddress;
		

	public:
		WowObject(unsigned int baseAddress) { 
			this->baseAddress = baseAddress; 
			this->descriptorAddress = getMemoryReader()->readInt(this->baseAddress + DESCRIPTOR_OFFSET);
		}
		~WowObject() {}

	public:
		int getBaseAddress() { return  this->baseAddress;  }
		int getGuid() { return getMemoryReader()->readInt(this->baseAddress + GUID_OFFSET); }
		int getDescriptorAddress() { int descriptor = getMemoryReader()->readInt(this->baseAddress + DESCRIPTOR_OFFSET); }

		Position* getPosition() {
			Position* position = new Position();
			position->posX = getMemoryReader()->readFloat(this->baseAddress + X_POS_OFFSET);
			position->posY = getMemoryReader()->readFloat(this->baseAddress + Y_POS_OFFSET);
			position->posZ = getMemoryReader()->readFloat(this->baseAddress + Z_POS_OFFSET);
			position->rotation = getMemoryReader()->readFloat(this->baseAddress + 0x09C4);

			return position;
		}

	protected:
		MemoryReader * getMemoryReader() { return MemoryReader::getInstance(); }
};