#pragma once

#include "PlayerController.h"
#include "PlayerPawn.h"

class CEntity
{
  public:
    PlayerController Controller;
    PlayerPawn Pawn;

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
        if (!this->Controller.GetPlayerName())
            return false;

        this->Pawn.Address = this->Controller.GetPlayerPawnAddress();

        return true;
    }

    bool UpdatePawn(const DWORD64 &PlayerPawnAddress)
    {
        if (PlayerPawnAddress == 0)
            return false;
        this->Pawn.Address = PlayerPawnAddress;

        if (!this->Pawn.GetCameraPos())
            return false;
        if (!this->Pawn.GetPos())
            return false;
        if (!this->Pawn.GetViewAngle())
            return false;
        if (!this->Pawn.GetWeaponName())
            return false;
        if (!this->Pawn.GetAimPunchAngle())
            return false;
        if (!this->Pawn.GetShotsFired())
            return false;
        if (!this->Pawn.GetHealth())
            return false;
        if (!this->Pawn.GetTeamID())
            return false;
        if (!this->Pawn.GetFov())
            return false;
        if (!this->Pawn.GetSpotted())
            return false;
        if (!this->Pawn.GetFFlags())
            return false;
        if (!this->Pawn.GetAimPunchCache())
            return false;

        return true;
    }

    bool IsAlive()
    {
        return this->Controller.AliveStatus == 1 && this->Pawn.Health > 0;
    }
};
