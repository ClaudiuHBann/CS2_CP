#pragma once

#include "IManager.h"
#include "ManagerProcess.h"
#include "Offsets.h"
#include "Signatures.h"

class ManagerOffsets : public IManager
{
    ManagerProcess &mManagerProcess;

  public:
    ManagerOffsets(ManagerProcess &aManagerProcess) : mManagerProcess(aManagerProcess)
    {
    }

    [[nodiscard]] inline std::uintptr_t SearchSignature(const std::string &aSignature,
                                                        const ManagerProcess::Module &aModule)
    {
        auto buffer = new unsigned char[aModule.mSize];
        mManagerProcess.ReadMemoryBuffer(aModule.mBase, buffer, aModule.mSize);

        const auto address = aModule.mBase + SearchMemory(aSignature.c_str(), buffer, aModule.mSize);

        uint32_t offset{};
        if (!mManagerProcess.ReadMemory(address + 3, offset))
        {
            return {};
        }

        return address + offset + 7;
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
