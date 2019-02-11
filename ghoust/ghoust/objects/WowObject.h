#pragma once

#include "MemoryReader.h"
#include "Position.h"

using namespace std;

class WowObject {
	protected:
		static const int GUID_OFFSET = 0x30;
		static const int TYPE_OFFSET = 0x14;
		static const int X_POS_OFFSET = 0x9B8;
		static const int Y_POS_OFFSET = 0x9BC;
		static const int Z_POS_OFFSET = 0x9BC + 4;
		static const int ROTATION_OFFSET = 0x09C4;
		static const int DESCRIPTOR_OFFSET = 0x8;
    
        static const int MAX_BUFF_SIZE = 16;

	protected:
		int baseAddress;
		int descriptorAddress;

	public:
		WowObject(int baseAddress) { 
			this->baseAddress = baseAddress; 
			this->descriptorAddress = getDescriptorAddress();
		}
		~WowObject() {}

	public:
		int getBaseAddress() { return  this->baseAddress;  }
		unsigned int getGuid() { return getMemoryReader()->readUnsignedInt(this->baseAddress + GUID_OFFSET); }
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

	protected:
		MemoryReader * getMemoryReader() { return MemoryReader::getInstance(); }
};
