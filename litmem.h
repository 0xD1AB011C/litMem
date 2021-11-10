#pragma once
#include <Windows.h> //General windows functions
#include <TlHelp32.h> //Snapshot management
#include <string>
#include <sstream> //String conversion operators
#include <vector>
#include "consts.h"

class litMem
{
private:
	uintptr_t addr; //FindDMAAddy
	PROCESSENTRY32 proc; //findProcID
	MODULEENTRY32 mod; //findModAddr
	HANDLE myHandle;
	DWORD procID = NULL;
	DWORD modAddr;

	HANDLE procHandle;

public:
	uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets);
	DWORD findProcID();
	DWORD findModAddr(std::string modTarg);
	DWORD readMem(DWORD target);

};

