#pragma once

#include <Windows.h>
#include "WindowManager.h"
#include "MemoryAddress.h"
#include "Guid.h"

class MemoryReader
{
	public:
		static MemoryReader* getInstance();
		~MemoryReader();

	private:
		MemoryReader();

		static MemoryReader* memoryReader;

		void initialize();
		void stop();
		void lookupPrivilege();
		void openProcess();
		void calculateWowBaseAddress();
		void calculateWowBaseAddress2();

	private:
		HANDLE processHandler;

	public:
		void readMemory();
		

		float readFloat(Address address);
		float readFloat(LPVOID address);
		float readFloat(int address);

		byte readByte(LPVOID address);
		byte readByte(int address);

		int readInt(Address address);
		int readInt(LPVOID address);
		int readInt(int address);

		unsigned int readUnsignedInt(LPVOID address);
		unsigned int readUnsignedInt(int address);
};
