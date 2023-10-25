#pragma once

#include "ManagerOffsets.h"
#include "ManagerProcess.h"
#include "Offsets.h"

class PlayerPawn
{
  public:
    enum class Flags
    {
        NONE,
        IN_AIR = 1 << 0
    };

    DWORD64 Address = 0;
    Vector2f ViewAngle;
    Vector2f ScreenPos;
    DWORD64 ShotsFired;
    Vector2f AimPunchAngle;
    int Health;
    int TeamID;
    int Fov;
    DWORD64 bSpottedByMask;
    int fFlags;

    PlayerPawn(ManagerProcess &aManagerProcess) : mManagerProcess(aManagerProcess)
    {
    }

    ManagerProcess &mManagerProcess;

  public:
    bool GetAimPunchAngle()
    {
        return mManagerProcess.ReadMemory<Vector2f>(Address + Offsets::Entity::aimPunchAngle, this->AimPunchAngle);
    }

    bool GetTeamID()
    {
        return mManagerProcess.ReadMemory<int>(Address + Offsets::Entity::iTeamNum, this->TeamID);
    }

    bool GetHealth()
    {
        return mManagerProcess.ReadMemory<int>(Address + Offsets::Entity::iHealth, this->Health);
    }

    bool GetFFlags()
    {
        return mManagerProcess.ReadMemory<int>(Address + Offsets::Entity::fFlags, this->fFlags);
    }

    constexpr bool HasFlag(const Flags Flag) const noexcept
    {
        return fFlags & (int)Flag;
    }
};
