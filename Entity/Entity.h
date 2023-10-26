#pragma once

#include "Controller.h"

class Entity
{
  public:
    constexpr Entity(ManagerProcess &aManagerProcess, ManagerGame &aManagerGame) noexcept
        : mManagerGame(aManagerGame), mPawn(aManagerProcess), mController(aManagerProcess, aManagerGame, mPawn)
    {
    }

    inline void UpdatePawn(const std::uintptr_t aBase = 0)
    {
        if (aBase)
        {
            mPawn.Base(aBase);
        }
        else
        {
            mPawn.Base(mManagerGame.GetLocalPawn());
        }

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
    ManagerGame &mManagerGame;

    Pawn mPawn;
    Controller mController;
};
