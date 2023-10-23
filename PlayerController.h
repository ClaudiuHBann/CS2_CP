#pragma once

#include "Game.h"
#include "ManagerOffsets.h"
#include "Offsets.h"

class PlayerController
{
  public:
    DWORD64 Address = 0;
    int TeamID = 0;
    int Health = 0;
    int AliveStatus = 0;
    DWORD64 Pawn = 0;
    std::string PlayerName;

  public:
    bool GetTeamID()
    {
        return ProcessManager::ReadMemory<int>(Address + Offsets::Entity::iTeamNum, this->TeamID);
    }

    bool GetHealth()
    {
        return ProcessManager::ReadMemory<int>(Address + Offsets::Entity::iHealth, this->Health);
    }

    bool GetIsAlive()
    {
        return ProcessManager::ReadMemory<int>(Address + Offsets::Entity::bIsAlive, this->AliveStatus);
    }

    DWORD64 GetPlayerPawnAddress()
    {
        DWORD64 EntityPawnListEntry = 0;
        DWORD64 EntityPawnAddress = 0;

        if (!ProcessManager::ReadMemory<DWORD64>(Address + Offsets::hPlayerPawn, this->Pawn))
            return 0;

        if (!ProcessManager::ReadMemory<DWORD64>(gGame.GetEntityListAddress(), EntityPawnListEntry))
            return 0;

        if (!ProcessManager::ReadMemory<DWORD64>(EntityPawnListEntry + 0x10 + 8 * ((Pawn & 0x7FFF) >> 9),
                                                 EntityPawnListEntry))
            return 0;

        if (!ProcessManager::ReadMemory<DWORD64>(EntityPawnListEntry + 0x78 * (Pawn & 0x1FF), EntityPawnAddress))
            return 0;

        return EntityPawnAddress;
    }
};
