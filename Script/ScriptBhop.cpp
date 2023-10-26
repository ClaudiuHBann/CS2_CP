#include "pch.h"
#include "ScriptBhop.h"

void ScriptBhop::Update()
{
    const bool hasFlagInAir = !mEntityLocal.GetPawn().HasFlag(Pawn::Flags::IN_AIR);
    if (GetAsyncKeyState(VK_SPACE) && hasFlagInAir)
    {
        mManagerGame.SetForceJump(256); // set flag for jumping
    }
    else if (GetAsyncKeyState(VK_SPACE) && !hasFlagInAir)
    {
        mManagerGame.SetForceJump(65537); // set flag for not jumping
    }
}
