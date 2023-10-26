#pragma once

#include "Controller.h"

class Entity
{
  public:
    constexpr Entity(ManagerProcess &aManagerProcess, ManagerGame &aManagerGame) noexcept
        : mManagerGame(aManagerGame), mPawn(aManagerProcess), mController(aManagerProcess, aManagerGame, mPawn)
    {
    }

    void UpdatePawn(const std::uintptr_t aBase);

    [[nodiscard]] constexpr Pawn &GetPawn() noexcept
    {
        return mPawn;
    }

  private:
    ManagerGame &mManagerGame;

    Pawn mPawn;
    Controller mController;
};
