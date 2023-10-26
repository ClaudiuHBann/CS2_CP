#include "pch.h"
#include "ScriptTriggerbot.h"

void ScriptTriggerbot::Update()
{
    DWORD uHandle = 0;
    if (!mManagerProcess.ReadMemory(mEntityLocal.GetPawn().Base() + Offsets::Entity::iIDEntIndex, uHandle))
        return;
    if (uHandle == -1)
        return;

    DWORD64 ListEntry = 0;
    ListEntry = mManagerProcess.TraceAddress(mManagerGame.GetEntityListAddress(), {0x8 * (uHandle >> 9) + 0x10, 0x0});
    if (ListEntry == 0)
        return;

    DWORD64 PawnAddress = 0;
    if (!mManagerProcess.ReadMemory<DWORD64>(ListEntry + 0x78 * (uHandle & 0x1FF), PawnAddress))
        return;

    Entity Entity(mManagerProcess, mManagerGame);
    Entity.UpdatePawn(PawnAddress);

    bool AllowShoot =
        mEntityLocal.GetPawn().iTeamNum() != Entity.GetPawn().iTeamNum() && Entity.GetPawn().iHealth() > 0;
    if (!AllowShoot)
        return;

    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}
