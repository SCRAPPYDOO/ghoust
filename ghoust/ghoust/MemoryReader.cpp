#include "stdafx.h"
#include "MemoryReader.h"
#include <tchar.h>
#include <stdio.h>
#include <psapi.h>
#include <TlHelp32.h> //PROCESSENTRY
#include <iomanip>

#pragma comment(lib, "psapi.lib")

using namespace std;

#define UNINITIALIZED 0xFFFFFFFF

MemoryReader::MemoryReader(DWORD processId) {
	this->lookupPrivilege();
	this->openProcess(processId);
	this->processId = processId;
	//this->calculateWowBaseAddress();
	//this->calculateWowBaseAddress2();
}

MemoryReader::~MemoryReader()
{
	CloseHandle(processHandler);
}

void MemoryReader::lookupPrivilege() {

	BOOL               bRET = FALSE;
	TOKEN_PRIVILEGES   tp;
	HANDLE             hToken;

	if (LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid))
	{
		if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken))
		{
			if (hToken != INVALID_HANDLE_VALUE)
			{
				tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
				tp.PrivilegeCount = 1;
				if (AdjustTokenPrivileges(hToken, FALSE, &tp, 0, 0, 0)) {
					bRET = TRUE;
				}
				CloseHandle(hToken);
			}
		}
		else {
			cout << "Cant open process token: error: " << GetLastError() << endl;
		}
	}
}

void MemoryReader::openProcess(DWORD processId)
{
	this->processHandler = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);

	if (processHandler != NULL) {
		cout << "Process opened " << processHandler << endl;
	}
	else {
		cout << "Cant open process: " << processId << " last error " << GetLastError() << endl;
		getchar();
	}
}

void MemoryReader::calculateWowBaseAddress()
{


	if (NULL != processHandler)
	{
		HMODULE hMod[1024];
		DWORD cbNeeded;
		MODULEINFO info;

		if (EnumProcessModulesEx(processHandler, hMod, sizeof(hMod), &cbNeeded, LIST_MODULES_32BIT | LIST_MODULES_64BIT))
		{
			
			for (int i = 0; i < (cbNeeded / sizeof(HMODULE)); i++) {
				TCHAR szModName1[MAX_PATH];
				if (GetModuleFileNameEx(processHandler, hMod[i], szModName1, sizeof(szModName1) / sizeof(TCHAR)))
				{
					wstring wstrModName = szModName1;
					//you will need to change this to the name of the exe of the foreign process
					wstring wstrModContain = L"WoW.exe";
					if (wstrModName.find(wstrModContain) != string::npos)
					{
						cout << "GetModuleFileNameEx " << (DWORD)hMod[i] << endl;
						cout << "GetModuleFileNameEx " << hMod[i] << endl;
						cout << "GetModuleFileNameEx " << (LPVOID)hMod[i] << endl;
					}
				}
			}
		}
	}
}

void MemoryReader::calculateWowBaseAddress2() {
	HANDLE moduleSnapshotHandle_ = INVALID_HANDLE_VALUE;
	MODULEENTRY32 moduleEntry_;

	DWORD  processBaseAddress_ = UNINITIALIZED;
	const wchar_t* txt = L"Hello World";
	/* Take snapshot of all the modules in the process */
	moduleSnapshotHandle_ = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, this->processId);

	/* Snapshot failed */
	if (moduleSnapshotHandle_ == INVALID_HANDLE_VALUE)
	{
		std::cout << "Module Snapshot error" << std::endl;
		return;
	}

	/* Size the structure before usage */
	moduleEntry_.dwSize = sizeof(MODULEENTRY32);

	/* Retrieve information about the first module */
	if (!Module32First(moduleSnapshotHandle_, &moduleEntry_))
	{
		std::cout << "First module not found" << std::endl;
		CloseHandle(moduleSnapshotHandle_);
		return;
	}

	/* Find base address */
	while (processBaseAddress_ == UNINITIALIZED)
	{
		/* Find module of the executable */
		do
		{

			/* Compare the name of the process to the one we want */
			//if (!strcmp(moduleEntry_.szModule, txt)) //?
			//{
				/* Save the processID and break out */
				processBaseAddress_ = (unsigned int)moduleEntry_.modBaseAddr;
				cout << "calculateWowBaseAddress2 proces address " << processBaseAddress_ << endl;
				//break;
			//}

		} while (Module32Next(moduleSnapshotHandle_, &moduleEntry_));


		if (processBaseAddress_ == UNINITIALIZED)
		{
			system("CLS");
			std::cout << "Failed to find module" << "" << std::endl;
			Sleep(200);
		}
	}

	/* Found module and base address successfully */
	std::cout << "Base Address: " << std::hex << processBaseAddress_ << std::dec << std::endl;
	CloseHandle(moduleSnapshotHandle_);
}

void MemoryReader::readMemory() {

	cout << "Reading memory" << endl;

	int objectManager = this->readInt(Address::OBJECT_MANAGER);
	cout << " Object Manager " << &objectManager << endl;

	int currentObject = this->readInt((LPVOID)(objectManager + Address::FIRST_OBJECT));

	while (currentObject != 0 && (currentObject & 1) == 0)
	{
		int type = this->readInt((LPVOID)(currentObject + Address::OBJECT_TYPE));
		cout << "Object: " << currentObject << " type: " << type << endl;

		long int guid = this->readInt((LPVOID)(currentObject + Address::OBJECT_GUID));
		cout << "Object: " << currentObject << " guid: " << guid << endl;


		int descriptor = this->readInt((LPVOID)(currentObject + Address::DESCIPROT));
		int health = this->readInt((LPVOID)(descriptor + Address::OBJECT_HEALTH));
		cout << " health: " << health << endl;

		int nextObject = this->readInt((LPVOID)(currentObject + Address::NEXT_OBJECT));
		if (nextObject == currentObject) {
			break;
		} else {
			currentObject = nextObject;
		}
	}
}

int MemoryReader::readInt(LPVOID address) {
	int value;
	if (ReadProcessMemory(this->processHandler, address, &value, sizeof(value), NULL)) {
		return value;
	}
}

int MemoryReader::readInt(Address address) {
	int value;
	if (ReadProcessMemory(this->processHandler, (LPVOID)address, &value, sizeof(value), NULL)) {
		return value;
	}
}

float MemoryReader::readFloat(Address address) {
	float value;
	if (ReadProcessMemory(this->processHandler, (LPVOID)address, &value, sizeof(value), NULL)) {
		return value;
	}
}

int MemoryReader::getPlayerLevel()
{
	return readInt(Address::PLAYER_LEVEL);
}

float MemoryReader::getPlayerPositionX() {
	return readFloat(Address::PLAYER_POSITION_X);
}
