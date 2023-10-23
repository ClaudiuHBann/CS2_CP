#pragma once

#include "ManagerProcess.h"
#include "Offsets.h"
#include "Signatures.h"

template <typename T> static inline bool GetDataAddressWithOffset(const DWORD64 &Address, DWORD64 Offset, T &Data)
{
    if (Address == 0)
        return false;

    if (!ProcessManager::ReadMemory<T>(Address + Offset, Data))
        return false;

    return true;
}

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

    TempAddress = SearchOffsets(Offset::Signatures::EntityList, ClientDLL);
    if (TempAddress == 0)
        return false;

    Offset::EntityList = TempAddress - ClientDLL;

    TempAddress = SearchOffsets(Offset::Signatures::LocalPlayerController, ClientDLL);
    if (TempAddress == 0)
        return false;

    Offset::LocalPlayerController = TempAddress - ClientDLL;

    TempAddress = SearchOffsets(Offset::Signatures::ViewMatrix, ClientDLL);
    if (TempAddress == 0)
        return false;

    Offset::Matrix = TempAddress - ClientDLL;

    TempAddress = SearchOffsets(Offset::Signatures::GlobalVars, ClientDLL);
    if (TempAddress == 0)
        return false;

    Offset::GlobalVars = TempAddress - ClientDLL;

    TempAddress = SearchOffsets(Offset::Signatures::ViewAngles, ClientDLL);
    if (TempAddress == 0)
        return false;
    if (!ProcessManager::ReadMemory(TempAddress, TempAddress))
        return false;

    Offset::ViewAngle = TempAddress + 0x4510 - ClientDLL;

    TempAddress = SearchOffsets(Offset::Signatures::LocalPlayerPawn, ClientDLL);
    if (TempAddress == 0)
        return false;

    Offset::LocalPlayerPawn = TempAddress + 0x118 - ClientDLL;

    TempAddress = SearchOffsets(Offset::Signatures::ForceJump, ClientDLL);
    if (TempAddress == 0)
        return false;

    Offset::ForceJump = TempAddress + 0x30 - ClientDLL;
    return true;
}
