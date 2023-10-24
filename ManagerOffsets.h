#pragma once

#include "IManager.h"
#include "ManagerProcess.h"
#include "Offsets.h"
#include "Signatures.h"

class ManagerOffsets : public IManager
{
    ManagerProcess &mManagerProcess;
    ManagerSignatures &mManagerSignatures;

  public:
    ManagerOffsets(ManagerProcess &aManagerProcess, ManagerSignatures &aManagerSignatures)
        : mManagerProcess(aManagerProcess), mManagerSignatures(aManagerSignatures)
    {
    }

    [[nodiscard]] inline std::uintptr_t SearchSignature(const std::string &aSignature,
                                                        const ManagerProcess::Module &aModule)
    {
        const auto addresses =
            mManagerSignatures.SearchMemory(aSignature, aModule.mBase, aModule.mBase + aModule.mSize);
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

    [[nodiscard]] inline void Initialize() override
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
