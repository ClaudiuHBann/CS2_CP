#pragma once

#include "Controller.h"

class Entity
{
  public:
    Entity(ManagerProcess &aManagerProcess, ManagerGame &aManagerGame)
        : mPawn(aManagerProcess), mController(aManagerProcess, aManagerGame, mPawn)
    {
    }

    inline void UpdateController(const std::uintptr_t aBase)
    {
        if (!aBase)
        {
            return;
        }

        mController.Base(aBase);
        mPawn.Base(mController.FindPawnAddress());
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
