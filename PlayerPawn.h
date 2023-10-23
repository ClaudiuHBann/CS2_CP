#pragma once

#include "ManagerOffsets.h"
#include "Vector.h"

class PlayerPawn
{
  public:
    enum class Flags
    {
        NONE,
        IN_AIR = 1 << 0
    };

    DWORD64 Address = 0;
    Vec2 ViewAngle;
    Vec3 Pos;
    Vec2 ScreenPos;
    Vec3 CameraPos;
    std::string WeaponName;
    DWORD64 ShotsFired;
    Vec2 AimPunchAngle;
    C_UTL_VECTOR AimPunchCache;
    int Health;
    int TeamID;
    int Fov;
    DWORD64 bSpottedByMask;
    int fFlags;

  public:
    bool GetAimPunchAngle()
    {
        return ProcessManager::ReadMemory<Vec2>(Address + Offsets::Entity::aimPunchAngle, this->AimPunchAngle);
    }

    bool GetTeamID()
    {
        return ProcessManager::ReadMemory<int>(Address + Offsets::Entity::iTeamNum, this->TeamID);
    }

    bool GetHealth()
    {
        return ProcessManager::ReadMemory<int>(Address + Offsets::Entity::iHealth, this->Health);
    }

    bool GetFFlags()
    {
        return ProcessManager::ReadMemory<int>(Address + Offsets::Entity::fFlags, this->fFlags);
    }

    constexpr bool HasFlag(const Flags Flag) const noexcept
    {
        return fFlags & (int)Flag;
    }
};
