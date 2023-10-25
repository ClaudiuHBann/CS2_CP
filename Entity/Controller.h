#pragma once

#include "Manager/ManagerGame.h"
#include "Manager/ManagerProcess.h"
#include "Pawn.h"

// TODO: check if this is actually useless
class Controller
{
    DEFINE_BASE;

  public:
    constexpr Controller(ManagerProcess &aManagerProcess, ManagerGame &aManagerGame, Pawn &aPawn) noexcept
        : mManagerProcess(aManagerProcess), mManagerGame(aManagerGame), mPawn(aPawn)
    {
    }

  private:
    ManagerProcess &mManagerProcess;
    ManagerGame &mManagerGame;
    Pawn &mPawn;
};
