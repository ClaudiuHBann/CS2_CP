#pragma once

#include "ManagerProcess.h"
#include "Offsets.h"
#include "Vector.h"

class ManagerGame : public IManager
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

    ManagerProcess &mManagerProcess;

  public:
    ManagerGame(ManagerProcess &aManagerProcess) : mManagerProcess(aManagerProcess)
    {
    }

    void Initialize() override
    {
        this->Address.ClientDLL = mManagerProcess.GetModuleClient().mBase;

        this->Address.EntityList = GetClientDLLAddress() + Offsets::dwEntityList;
        this->Address.LocalController = GetClientDLLAddress() + Offsets::dwLocalPlayerController;
        this->Address.LocalPawn = GetClientDLLAddress() + Offsets::dwLocalPlayerPawn;
        this->Address.ForceJump = GetClientDLLAddress() + Offsets::dwForceJump;
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
        if (!mManagerProcess.ReadMemory<DWORD64>(GetEntityListAddress(), EntityListEntry))
            return false;
        if (!mManagerProcess.ReadMemory<DWORD64>(EntityListEntry + 0x10, EntityListEntry))
            return false;

        this->Address.EntityListEntry = EntityListEntry;

        return this->Address.EntityListEntry != 0;
    }

    bool SetViewAngle(float Yaw, float Pitch)
    {
        Vector2f Angle{Pitch, Yaw};

        if (!mManagerProcess.WriteMemory<Vector2f>(this->Address.ViewAngle, Angle))
            return false;

        return true;
    }

    bool SetForceJump(int value)
    {
        if (!mManagerProcess.WriteMemory<int>(this->Address.ForceJump, value))
            return false;

        return true;
    }
};
