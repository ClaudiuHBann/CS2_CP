#pragma once

// https://www.unknowncheats.me/forum/counter-strike-2-a/576077-counter-strike-2-reversal-structs-offsets-89.html
namespace Offset
{
inline DWORD64 EntityList;
inline DWORD64 Matrix;
inline DWORD64 ViewAngle;
inline DWORD64 LocalPlayerController;
inline DWORD64 LocalPlayerPawn;
inline DWORD64 ForceJump;
inline DWORD64 GlobalVars;

struct
{
    DWORD64 Health = 0x32C;
    DWORD64 TeamID = 0x3BF;
    DWORD64 IsAlive = 0x7C4;
    DWORD64 PlayerPawn = 0x7BC;
    DWORD64 iszPlayerName = 0x610;
} Entity;

struct
{
    DWORD64 Pos = 0x1214;
    DWORD64 MaxHealth = 0x328;
    DWORD64 CurrentHealth = 0x32C;
    DWORD64 GameSceneNode = 0x310;
    DWORD64 BoneArray = 0x1E0;
    DWORD64 angEyeAngles = 0x1500;
    DWORD64 vecLastClipCameraPos = 0x1274;
    DWORD64 pClippingWeapon = 0x1290;
    DWORD64 iShotsFired = 0x1404;
    DWORD64 flFlashDuration = 0x1450;
    DWORD64 aimPunchAngle = 0x1704;
    DWORD64 aimPunchCache = 0x1728;
    DWORD64 iIDEntIndex = 0x152C;
    DWORD64 iTeamNum = 0x3BF;
    DWORD64 CameraServices = 0x10E0;
    DWORD64 iFovStart = 0x214;
    DWORD64 fFlags = 0x3C8;
    DWORD64 bSpottedByMask = 0x1620 + 0xC; // entitySpottedState + bSpottedByMask
} Pawn;

struct
{
    DWORD64 RealTime = 0x00;
    DWORD64 FrameCount = 0x04;
    DWORD64 MaxClients = 0x10;
    DWORD64 IntervalPerTick = 0x14;
    DWORD64 CurrentTime = 0x2C;
    DWORD64 CurrentTime2 = 0x30;
    DWORD64 TickCount = 0x40;
    DWORD64 IntervalPerTick2 = 0x44;
    DWORD64 CurrentNetchan = 0x0048;
    DWORD64 CurrentMap = 0x0180;
    DWORD64 CurrentMapName = 0x0188;
} GlobalVar;
} // namespace Offset
