#include <iostream>
#include "litmem.h"

int main()
{
    litMem mem; //Create instance of memory class
    DWORD procID = mem.findProcID(); //Fetch process ID, process target found in 'consts.h'
    DWORD client = mem.findModAddr("client.dll");

    DWORD localPlayer = mem.readMem(client + 0xDA747C);
    DWORD localHP = mem.readMem(localPlayer + 0x100);
    std::cout << localHP;
}