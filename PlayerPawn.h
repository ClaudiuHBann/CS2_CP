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
    bool GetViewAngle()
    {
        return GetDataAddressWithOffset<Vec2>(Address, Offset::Pawn.angEyeAngles, this->ViewAngle);
    }

    bool GetCameraPos()
    {
        return GetDataAddressWithOffset<Vec3>(Address, Offset::Pawn.vecLastClipCameraPos, this->CameraPos);
    }

    bool GetSpotted()
    {
        return GetDataAddressWithOffset<DWORD64>(Address, Offset::Pawn.bSpottedByMask, this->bSpottedByMask);
    }

    bool GetWeaponName()
    {
        DWORD64 WeaponNameAddress = 0;
        char Buffer[MAX_PATH]{};

        WeaponNameAddress =
            ProcessManager::TraceAddress(this->Address + Offset::Pawn.pClippingWeapon, {0x10, 0x20, 0x0});
        if (WeaponNameAddress == 0)
            return false;

        if (!ProcessManager::ReadMemory(WeaponNameAddress, Buffer, MAX_PATH))
            return false;

        WeaponName = std::string(Buffer);
        std::size_t Index = WeaponName.find("_");
        if (Index == std::string::npos || WeaponName.empty())
        {
            WeaponName = "Weapon_None";
        }
        else
        {
            WeaponName = WeaponName.substr(Index + 1, WeaponName.size() - Index - 1);
        }

        return true;
    }

    bool GetShotsFired()
    {
        return GetDataAddressWithOffset<DWORD64>(Address, Offset::Pawn.iShotsFired, this->ShotsFired);
    }

    bool GetAimPunchAngle()
    {
        return GetDataAddressWithOffset<Vec2>(Address, Offset::Pawn.aimPunchAngle, this->AimPunchAngle);
    }

    bool GetTeamID()
    {
        return GetDataAddressWithOffset<int>(Address, Offset::Pawn.iTeamNum, this->TeamID);
    }

    bool GetAimPunchCache()
    {
        return GetDataAddressWithOffset<C_UTL_VECTOR>(Address, Offset::Pawn.aimPunchCache, this->AimPunchCache);
    }

    bool GetPos()
    {
        return GetDataAddressWithOffset<Vec3>(Address, Offset::Pawn.Pos, this->Pos);
    }

    bool GetHealth()
    {
        return GetDataAddressWithOffset<int>(Address, Offset::Pawn.CurrentHealth, this->Health);
    }

    bool GetFov()
    {
        DWORD64 CameraServices = 0;
        if (!ProcessManager::ReadMemory<DWORD64>(Address + Offset::Pawn.CameraServices, CameraServices))
            return false;
        return GetDataAddressWithOffset<int>(CameraServices, Offset::Pawn.iFovStart, this->Fov);
    }

    bool GetFFlags()
    {
        return GetDataAddressWithOffset<int>(Address, Offset::Pawn.fFlags, this->fFlags);
    }

    constexpr bool HasFlag(const Flags Flag) const noexcept
    {
        return fFlags & (int)Flag;
    }
};
