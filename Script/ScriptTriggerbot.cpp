#include "pch.h"
#include "ScriptTriggerbot.h"

void ScriptTriggerbot::Update()
{
    const auto iIDEntIndex =
        mManagerProcess.ReadMemory<uint32_t>(mEntityLocal.GetPawn().Base() + Offsets::Entity::iIDEntIndex);
    if (iIDEntIndex == -1)
    {
        return;
    }

    // TODO: explain magic numbers
    const auto entityListEntry =
        mManagerProcess.TraceAddress(mManagerGame.GetEntityListAddress(), 0x8 * (iIDEntIndex >> 9) + 0x10);
    if (!entityListEntry)
    {
        return;
    }

    Entity Entity(mManagerProcess, mManagerGame);
    const auto pawnAddress = mManagerProcess.ReadMemory<std::uintptr_t>(entityListEntry + 0x78 * (iIDEntIndex & 0x1FF));
    Entity.UpdatePawn(pawnAddress);

    const auto shoot = mEntityLocal.GetPawn().iTeamNum() != Entity.GetPawn().iTeamNum() && Entity.GetPawn().iHealth();
    if (!shoot)
    {
        return;
    }

    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}
