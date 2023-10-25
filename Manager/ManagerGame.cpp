#include "pch.h"
#include "ManagerGame.h"
#include "Utility/Offsets.h"

void ManagerGame::Initialize()
{
    auto moduleClient = mManagerProcess.GetModuleClient().mBase;

    mEntityList = moduleClient + Offsets::dwEntityList;
    mLocalController = moduleClient + Offsets::dwLocalController;
    mLocalPawn = moduleClient + Offsets::dwLocalPawn;
}

bool ManagerGame::SetForceJump(const int aValue) const
{
    return mManagerProcess.WriteMemory(mForceJump, aValue);
}
