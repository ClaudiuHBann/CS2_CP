#pragma once

#include "IManager.h"
#include "ManagerProcess.h"
#include "ManagerSignatures.h"
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

    [[nodiscard]] inline void Initialize() override
    {
        const auto &moduleClientDLL = mManagerProcess.GetModuleClient();
        if (!moduleClientDLL.mBase)
        {
            return;
        }

        // TODO: add this to managersignatures
        std::vector<std::uint8_t> data(moduleClientDLL.mSize);
        mManagerProcess.ReadMemoryBuffer(moduleClientDLL.mBase, data.data(), data.size());

        Offsets::dwForceJump = mManagerSignatures.FindSignature(data, moduleClientDLL, Signatures::dwForceJump);

        Offsets::dwEntityList = mManagerSignatures.FindSignature(data, moduleClientDLL, Signatures::dwEntityList);

        Offsets::dwLocalPlayerController =
            mManagerSignatures.FindSignature(data, moduleClientDLL, Signatures::dwLocalPlayerController);
        Offsets::dwLocalPlayerPawn =
            mManagerSignatures.FindSignature(data, moduleClientDLL, Signatures::dwLocalPlayerPawn);
    }
};
