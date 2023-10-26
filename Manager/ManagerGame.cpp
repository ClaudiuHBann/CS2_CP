#include "pch.h"
#include "ManagerGame.h"
#include "Utility/Offsets.h"

void ManagerGame::Initialize()
{
    auto moduleClient = mManagerProcess.GetModuleClient().mBase;

    mForceJump = moduleClient + Offsets::dwForceJump;

    mEntityList = moduleClient + Offsets::dwEntityList;

    mLocalPawn = moduleClient + Offsets::dwLocalPawn;
    mLocalController = moduleClient + Offsets::dwLocalController;
}

bool ManagerGame::SetForceJump(const int aValue) const
{
    return mManagerProcess.WriteMemory(mForceJump, aValue);
}
