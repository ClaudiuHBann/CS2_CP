#pragma once

#include "ManagerProcess.h"
#include "Offsets.h"
#include "Signatures.h"

static DWORD64 SearchOffsets(std::string Signature, DWORD64 ModuleAddress)
{
    std::vector<DWORD64> TempAddressList;
    DWORD64 Address = 0;
    DWORD Offsets = 0;

    TempAddressList = ProcessManager::SearchMemory(Signature, ModuleAddress, ModuleAddress + 0x4000000);

    if (TempAddressList.size() <= 0)
        return 0;

    if (!ProcessManager::ReadMemory<DWORD>(TempAddressList.at(0) + 3, Offsets))
        return 0;

    Address = TempAddressList.at(0) + Offsets + 7;
    return Address;
}

static inline bool UpdateOffsets()
{
    DWORD64 ClientDLL = reinterpret_cast<DWORD64>(ProcessManager::GetProcessModuleHandle("client.dll"));
    if (ClientDLL == 0)
        return false;

    DWORD64 TempAddress = 0;

    TempAddress = SearchOffsets(Signatures::EntityList, ClientDLL);
    if (TempAddress == 0)
        return false;

    Offsets::dwEntityList = TempAddress - ClientDLL;

    TempAddress = SearchOffsets(Signatures::LocalPlayerController, ClientDLL);
    if (TempAddress == 0)
        return false;

    Offsets::dwLocalPlayerController = TempAddress - ClientDLL;

    TempAddress = SearchOffsets(Signatures::LocalPlayerPawn, ClientDLL);
    if (TempAddress == 0)
        return false;

    Offsets::dwLocalPlayerPawn = TempAddress + 0x118 - ClientDLL;

    TempAddress = SearchOffsets(Signatures::ForceJump, ClientDLL);
    if (TempAddress == 0)
        return false;

    Offsets::dwForceJump = TempAddress + 0x30 - ClientDLL;
    return true;
}
