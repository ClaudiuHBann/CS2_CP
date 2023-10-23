#pragma once

#include "ManagerProcess.h"
#include "Offsets.h"
#include "Vector.h"

class CGame
{
  private:
    struct
    {
        DWORD64 ClientDLL;
        DWORD64 EntityList;
        DWORD64 Matrix;
        DWORD64 ViewAngle;
        DWORD64 EntityListEntry;
        DWORD64 LocalController;
        DWORD64 LocalPawn;
        DWORD64 ForceJump;
        DWORD64 GlobalVars;
    } Address;

  public:
    bool InitAddress()
    {
        this->Address.ClientDLL = reinterpret_cast<DWORD64>(ProcessManager::GetProcessModuleHandle("client.dll"));

        this->Address.EntityList = GetClientDLLAddress() + Offset::EntityList;
        this->Address.Matrix = GetClientDLLAddress() + Offset::Matrix;
        this->Address.ViewAngle = GetClientDLLAddress() + Offset::ViewAngle;
        this->Address.LocalController = GetClientDLLAddress() + Offset::LocalPlayerController;
        this->Address.LocalPawn = GetClientDLLAddress() + Offset::LocalPlayerPawn;
        this->Address.ForceJump = GetClientDLLAddress() + Offset::ForceJump;
        this->Address.GlobalVars = GetClientDLLAddress() + Offset::GlobalVars;

        return this->Address.ClientDLL != 0;
    }

    DWORD64 GetClientDLLAddress()
    {
        return this->Address.ClientDLL;
    }

    DWORD64 GetEntityListAddress()
    {
        return this->Address.EntityList;
    }

    DWORD64 GetMatrixAddress()
    {
        return this->Address.Matrix;
    }

    DWORD64 GetViewAngleAddress()
    {
        return this->Address.ViewAngle;
    }

    DWORD64 GetEntityListEntry()
    {
        return this->Address.EntityListEntry;
    }

    DWORD64 GetLocalControllerAddress()
    {
        return this->Address.LocalController;
    }

    DWORD64 GetLocalPawnAddress()
    {
        return this->Address.LocalPawn;
    }

    DWORD64 GetGlobalVarsAddress()
    {
        return this->Address.GlobalVars;
    }

    bool UpdateEntityListEntry()
    {
        DWORD64 EntityListEntry = 0;
        if (!ProcessManager::ReadMemory<DWORD64>(GetEntityListAddress(), EntityListEntry))
            return false;
        if (!ProcessManager::ReadMemory<DWORD64>(EntityListEntry + 0x10, EntityListEntry))
            return false;

        this->Address.EntityListEntry = EntityListEntry;

        return this->Address.EntityListEntry != 0;
    }

    bool SetViewAngle(float Yaw, float Pitch)
    {
        Vec2 Angle{Pitch, Yaw};

        if (!ProcessManager::WriteMemory<Vec2>(this->Address.ViewAngle, Angle))
            return false;

        return true;
    }

    bool SetForceJump(int value)
    {
        if (!ProcessManager::WriteMemory<int>(this->Address.ForceJump, value))
            return false;

        return true;
    }
} static gGame;
