#include "pch.h"
#include "ManagerGame.h"
#include "ManagerProcess.h"
#include "Offsets.h"

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

/* [[nodiscard]] */ std::uintptr_t ManagerGame::GetEntityListEntryAddress()
{
    if (!mManagerProcess.ReadMemory(GetEntityListAddress(), mEntityListEntry))
    {
        return {};
    }

    if (!mManagerProcess.ReadMemory(mEntityListEntry + 0x10, mEntityListEntry))
    {
        return {};
    }

    return mEntityListEntry;
}
