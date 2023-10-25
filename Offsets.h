#pragma once

namespace Offsets
{
// offsets that will be found by signatures
inline std::ptrdiff_t dwForceJump{};

inline std::ptrdiff_t dwEntityList{};

inline std::ptrdiff_t dwLocalPawn{};
inline std::ptrdiff_t dwLocalController{};

constexpr std::ptrdiff_t hPlayerPawn = 0x7BC;

namespace Entity
{
constexpr std::ptrdiff_t bIsAlive = 0x7C4;
constexpr std::ptrdiff_t iHealth = 0x32C;
constexpr std::ptrdiff_t flFlashDuration = 0x1450;
constexpr std::ptrdiff_t aimPunchAngle = 0x1704;
constexpr std::ptrdiff_t iIDEntIndex = 0x152C;
constexpr std::ptrdiff_t iTeamNum = 0x3BF;
constexpr std::ptrdiff_t fFlags = 0x3C8;
}; // namespace Entity
} // namespace Offsets
