#include "pch.h"
#include "Entity.h"

void Entity::UpdatePawn(const std::uintptr_t aBase)
{
    mPawn.Base(aBase);

    mPawn.aimPunchAngle();
    mPawn.iHealth();
    mPawn.iTeamNum();
    mPawn.fFlags();
}
