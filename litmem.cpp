#include "litmem.h"
#include <iostream>

uintptr_t litMem::FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets)
{
    uintptr_t addr = ptr;
    for (unsigned int i = 0; i < offsets.size(); ++i)
    {
        ReadProcessMemory(hProc, (BYTE*)addr, &addr, sizeof(addr), 0);
        addr += offsets[i];
    }
    return addr;
}


DWORD litMem::findProcID()
{
    proc.dwSize = sizeof(PROCESSENTRY32);
    myHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); //Create snapshot of all processes
    while (Process32Next(myHandle, &proc)) //Iterate through all processes
    {
        char output[256];
        sprintf_s(output, "%ws", proc.szExeFile); //convert filename to comparable format

        if (output == targ)
        {
            procID = proc.th32ProcessID; //save PROC id if name matches and stop iterating
            break;
        }


    }
    if (procID != NULL) //If process was found print info about process
    {
        return procID;
    }
    else
    {
        return NULL;
    }
}

DWORD litMem::findModAddr(std::string modTarg)
{
    mod.dwSize = sizeof(MODULEENTRY32);
    if (procID != NULL)
    {
        procHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
        if (procHandle != NULL)
        {
            HANDLE modList = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, procID); //Fetches all 32bit modules in the process
            while (Module32Next(modList, &mod))
            {
                char output[256];
                sprintf_s(output, "%ws", mod.szModule); //convert filename to comparable format
                if (output == modTarg)
                {
                    modAddr = (DWORD)mod.modBaseAddr;
                    return modAddr;
                }
            }
            
        }
    }
    return NULL;
}

DWORD litMem::readMem(DWORD target)
{
    DWORD val = NULL;
    ReadProcessMemory(procHandle, (LPCVOID)(target), &val, sizeof(DWORD), 0);
    return val;
}