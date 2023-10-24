#pragma once

#include "ManagerProcess.h"
#include "Offsets.h"

class ManagerGame : public IManager
{
  private:
    DWORD64 ForceJump;

    DWORD64 EntityList;
    DWORD64 EntityListEntry;

    DWORD64 LocalPawn;
    DWORD64 LocalController;

    ManagerProcess &mManagerProcess;

  public:
    ManagerGame(ManagerProcess &aManagerProcess) : mManagerProcess(aManagerProcess)
    {
    }

    void Initialize() override
    {
        auto moduleClient = mManagerProcess.GetModuleClient().mBase;

        EntityList = moduleClient + Offsets::dwEntityList;
        LocalController = moduleClient + Offsets::dwLocalPlayerController;
        LocalPawn = moduleClient + Offsets::dwLocalPlayerPawn;
        ForceJump = moduleClient + Offsets::dwForceJump;
    }

    DWORD64 GetEntityListAddress()
    {
        return this->EntityList;
    }

    DWORD64 GetEntityListEntry()
    {
        return this->EntityListEntry;
    }

    DWORD64 GetLocalControllerAddress()
    {
        return this->LocalController;
    }

    bool UpdateEntityListEntry()
    {
        if (!mManagerProcess.ReadMemory<DWORD64>(GetEntityListAddress(), EntityListEntry))
            return false;
        if (!mManagerProcess.ReadMemory<DWORD64>(EntityListEntry + 0x10, EntityListEntry))
            return false;

        return this->EntityListEntry != 0;
    }

    DWORD64 GetLocalPawnAddress()
    {
        return this->LocalPawn;
    }

    bool SetForceJump(int value)
    {
        if (!mManagerProcess.WriteMemory<int>(this->ForceJump, value))
            return false;

        return true;
    }
};
