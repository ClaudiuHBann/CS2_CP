#include "pch.h"
#include "Entity.h"
#include "Game.h"
#include "ManagerOffsets.h"
#include "ManagerProcess.h"

int main()
{
    ManagerProcess managerProcess;
    managerProcess.Attach(L"cs2.exe");
    ManagerOffsets managerOffsets(managerProcess);
    managerOffsets.Initialize();
    CGame gGame(managerProcess);
    gGame.InitAddress();

    while (true)
    {
        // Update EntityList Entry
        gGame.UpdateEntityListEntry();

        DWORD64 LocalControllerAddress = 0;
        DWORD64 LocalPawnAddress = 0;

        if (!managerProcess.ReadMemory(gGame.GetLocalControllerAddress(), LocalControllerAddress))
            continue;
        if (!managerProcess.ReadMemory(gGame.GetLocalPawnAddress(), LocalPawnAddress))
            continue;

        // LocalEntity
        CEntity LocalEntity(managerProcess, gGame);
        static int LocalPlayerControllerIndex = 1;
        if (!LocalEntity.UpdateController(LocalControllerAddress))
            continue;
        if (!LocalEntity.UpdatePawn(LocalPawnAddress))
            continue;

        // AimBot data
        for (int i = 0; i < 64; i++)
        {
            CEntity Entity(managerProcess, gGame);
            DWORD64 EntityAddress = 0;
            if (!managerProcess.ReadMemory<DWORD64>(gGame.GetEntityListEntry() + (i + 1) * 0x78, EntityAddress))
                continue;

            if (EntityAddress == LocalEntity.Controller.Address)
            {
                LocalPlayerControllerIndex = i;
                continue;
            }

            if (!Entity.UpdateController(EntityAddress))
                continue;

            if (!Entity.UpdatePawn(Entity.Pawn.Address))
                continue;

            if (Entity.Controller.TeamID == LocalEntity.Controller.TeamID)
                continue;

            if (!Entity.IsAlive())
                continue;
        }

        float duration{};
        managerProcess.WriteMemory(LocalEntity.Pawn.Address + Offsets::Entity::flFlashDuration, duration);
    }

    return 0;
}
