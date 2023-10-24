#pragma once

#include "ManagerProcess.h"
#include "Offsets.h"
#include "Signatures.h"

class ManagerOffsets
{
  public:
    static std::uintptr_t SearchSignature(const std::string &aSignature, const std::uintptr_t &aBase,
                                          const std::size_t aSize)
    {
        std::vector<std::uintptr_t> TempAddressList;
        std::uintptr_t Address = 0;
        DWORD Offsets = 0;

        TempAddressList = ProcessManager::SearchMemory(aSignature, aBase, aBase + aSize);

        if (TempAddressList.size() <= 0)
            return 0;

        if (!ProcessManager::ReadMemory<DWORD>(TempAddressList.at(0) + 3, Offsets))
            return 0;

        Address = TempAddressList.at(0) + Offsets + 7;
        return Address;
    }

    static inline bool UpdateOffsets()
    {
        size_t size{};
        std::uintptr_t ClientDLL =
            reinterpret_cast<std::uintptr_t>(ProcessManager::GetProcessModuleHandle("client.dll", size));
        if (ClientDLL == 0)
            return false;

        std::ptrdiff_t TempAddress = 0;

        TempAddress = SearchSignature(Signatures::EntityList, ClientDLL, size);
        if (TempAddress == 0)
            return false;

        Offsets::dwEntityList = TempAddress - ClientDLL;

        TempAddress = SearchSignature(Signatures::LocalPlayerController, ClientDLL, size);
        if (TempAddress == 0)
            return false;

        Offsets::dwLocalPlayerController = TempAddress - ClientDLL;

        TempAddress = SearchSignature(Signatures::LocalPlayerPawn, ClientDLL, size);
        if (TempAddress == 0)
            return false;

        Offsets::dwLocalPlayerPawn = TempAddress + 0x118 - ClientDLL;

        TempAddress = SearchSignature(Signatures::ForceJump, ClientDLL, size);
        if (TempAddress == 0)
            return false;

        Offsets::dwForceJump = TempAddress + 0x30 - ClientDLL;
        return true;
    }
};
