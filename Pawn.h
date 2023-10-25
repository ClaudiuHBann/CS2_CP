#pragma once

#include "ManagerProcess.h"
#include "Offsets.h"

class Pawn
{
  public:
    enum class Flags : uint8_t
    {
        NONE,
        IN_AIR = 1 << 0
    };

    constexpr Pawn(ManagerProcess &aManagerProcess) noexcept : mManagerProcess(aManagerProcess)
    {
    }

    DEFINE_BASE;
    DEFINE_VAR_GET_SET(int, fFlags, Entity);
    DEFINE_VAR_GET_SET(int, iTeamNum, Entity);
    DEFINE_VAR_GET_SET(int, iHealth, Entity);
    DEFINE_VAR_GET_SET(Vector2f, aimPunchAngle, Entity);

    constexpr bool HasFlag(const Flags Flag) const noexcept
    {
        return mfFlags & (uint8_t)Flag;
    }

  private:
    ManagerProcess &mManagerProcess;
};
