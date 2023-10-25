#pragma once

#include "Controller.h"

class Entity
{
  public:
    constexpr Entity(ManagerProcess &aManagerProcess, ManagerGame &aManagerGame) noexcept
        : mPawn(aManagerProcess), mController(aManagerProcess, aManagerGame, mPawn)
    {
    }

    inline void UpdatePawn(const std::uintptr_t aBase)
    {
        if (!aBase)
        {
            return;
        }

        mPawn.Base(aBase);

        mPawn.aimPunchAngle();
        mPawn.iHealth();
        mPawn.iTeamNum();
        mPawn.fFlags();
    }

    [[nodiscard]] constexpr Pawn &GetPawn() noexcept
    {
        return mPawn;
    }

  private:
    Pawn mPawn;
    Controller mController;
};
