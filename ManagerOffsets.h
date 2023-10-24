#pragma once

#include "ManagerProcess.h"
#include "Offsets.h"
#include "Signatures.h"

class ManagerOffsets
{
    ManagerProcess &mManagerProcess;

  public:
    ManagerOffsets(ManagerProcess &aManagerProcess) : mManagerProcess(aManagerProcess)
    {
    }

    [[nodiscard]] inline std::uintptr_t SearchSignature(const std::string &aSignature,
                                                        const ManagerProcess::Module &aModule)
    {
        const auto addresses = SearchMemory(mManagerProcess, mManagerProcess.GetProcess(), aSignature, aModule.mBase,
                                            aModule.mBase + aModule.mSize);
        if (addresses.empty())
        {
            return {};
        }

        uint32_t offset{};
        if (!mManagerProcess.ReadMemory(addresses.front() + 3, offset))
        {
            return {};
        }

        return addresses.front() + offset + 7;
    }

    [[nodiscard]] inline void Initialize()
    {
        const auto &moduleClientDLL = mManagerProcess.GetModuleClient();
        if (!moduleClientDLL.mBase)
        {
            return;
        }

        auto address = SearchSignature(Signatures::EntityList, moduleClientDLL);
        Offsets::dwEntityList = address - moduleClientDLL.mBase;

        address = SearchSignature(Signatures::LocalPlayerController, moduleClientDLL);
        Offsets::dwLocalPlayerController = address - moduleClientDLL.mBase;

        address = SearchSignature(Signatures::LocalPlayerPawn, moduleClientDLL);
        Offsets::dwLocalPlayerPawn = address - moduleClientDLL.mBase + 0x118;

        address = SearchSignature(Signatures::ForceJump, moduleClientDLL);
        Offsets::dwForceJump = address - moduleClientDLL.mBase + 0x30;
    }
};
