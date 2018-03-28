#pragma once

#include "MemoryReader.h"

class WowObject {
	protected:
		static const int GUID_OFFSET = 0x30;
		static const int NEXT_OBJECT_OFFSET = 0x3C;
		static const int TYPE_OFFSET = 0x14;
		static const int X_POS_OFFSET = 0x7D0;
		static const int Y_POS_OFFSET = 0x7D4;
		static const int Z_POS_OFFSET = 0x7D8;
		static const int ROTATION_OFFSET = 0x7DC;
		static const int DESCRIPTOR_OFFSET = 0x8;

	protected:
		unsigned int baseAddress;
		MemoryReader* memoryReader = MemoryReader::getInstance();

	public:
		WowObject(unsigned int baseAddress) { this->baseAddress = baseAddress; }
		~WowObject() {}

	public:
		unsigned int getBaseAddress() { return  this->baseAddress;  }
		int getGuid() { return memoryReader->readInt(this->baseAddress + GUID_OFFSET); }
};