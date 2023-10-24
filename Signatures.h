#pragma once

namespace Signatures
{
constexpr Signature dwForceJump{L"48 8B 05 ?? ?? ?? ?? 48 8D 1D ?? ?? ?? ?? 48 89 45", 0x30};

constexpr Signature dwEntityList{L"48 8B 0D ?? ?? ?? ?? 48 89 7C 24 ?? 8B FA C1"};

constexpr Signature dwLocalPlayerPawn{L"48 8D 05 ?? ?? ?? ?? C3 CC CC CC CC CC CC CC CC 48 83 EC ?? 8B 0D", 0x118};
constexpr Signature dwLocalPlayerController{L"48 8B 05 ?? ?? ?? ?? 48 85 C0 74 4F"};
} // namespace Signatures
