#pragma once

#include "ManagerProcess.h"
#include "Offsets.h"
#include "Signatures.h"

class ManagerOffsets
{
  public:
    [[nodiscard]] static inline std::uintptr_t SearchSignature(const std::string &aSignature,
                                                               const ProcessManager::Module &aModule)
    {
        const auto addresses = ProcessManager::SearchMemory(aSignature, aModule.mBase, aModule.mBase + aModule.mSize);
        if (addresses.empty())
        {
            return {};
        }

        uint32_t offset{};
        if (!ProcessManager::ReadMemory(addresses.front() + 3, offset))
        {
            return {};
        }

        return addresses.front() + offset + 7;
    }

    [[nodiscard]] static inline void Initialize()
    {
        const auto moduleClientDLL = ProcessManager::GetProcessModuleHandle("client.dll");
        if (!moduleClientDLL.mBase)
        {
            return;
        }

        auto address = SearchSignature(Signatures::EntityList, moduleClientDLL);
        Offsets::dwEntityList = address - moduleClientDLL.mBase;

        address = SearchSignature(Signatures::LocalPlayerController, moduleClientDLL);
        Offsets::dwLocalPlayerController = address - moduleClientDLL.mBase;

        address = SearchSignature(Signatures::LocalPlayerPawn, moduleClientDLL);
        Offsets::dwLocalPlayerPawn = address + 0x118 - moduleClientDLL.mBase;

        address = SearchSignature(Signatures::ForceJump, moduleClientDLL);
        Offsets::dwForceJump = address + 0x30 - moduleClientDLL.mBase;
    }
};
