#pragma once

#include "Controller.h"
#include "Pawn.h"

class CEntity
{
  public:
    Controller Controller;
    Pawn Pawn;

    CEntity(ManagerProcess &aManagerProcess, ManagerGame &aManagerGame)
        : Controller(aManagerProcess, aManagerGame), Pawn(aManagerProcess)
    {
    }

  public:
    bool UpdateController(const DWORD64 &PlayerControllerAddress)
    {
        if (PlayerControllerAddress == 0)
            return false;
        this->Controller.Address = PlayerControllerAddress;

        if (!this->Controller.GetHealth())
            return false;
        if (!this->Controller.GetIsAlive())
            return false;
        if (!this->Controller.GetTeamID())
            return false;

        Pawn.Base(Controller.GetPlayerPawnAddress());

        return true;
    }

    void UpdatePawn(const std::uintptr_t aBase)
    {
        if (!aBase)
        {
            return;
        }

        Pawn.Base(aBase);

        Pawn.aimPunchAngle();
        Pawn.iHealth();
        Pawn.iTeamNum();
        Pawn.fFlags();
    }
};
