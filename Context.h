#pragma once

#include "Entity.h"
#include "ManagerGame.h"
#include "ManagerOffsets.h"
#include "ManagerProcess.h"
#include "ManagerSignatures.h"

class Context
{
    std::tuple<ManagerProcess *, ManagerSignatures *, ManagerOffsets *, ManagerGame *> mManagers{};

    [[nodiscard]] constexpr decltype(auto) GetManagerProcess() noexcept
    {
        return *std::get<ManagerProcess *>(mManagers);
    }

    [[nodiscard]] constexpr decltype(auto) GetManagerOffsets() noexcept
    {
        return *std::get<ManagerOffsets *>(mManagers);
    }

    [[nodiscard]] constexpr decltype(auto) GetManagerGame() noexcept
    {
        return *std::get<ManagerGame *>(mManagers);
    }

  public:
    Context()
    {
        auto managerProcess = new ManagerProcess;
        auto managerSignatures = new ManagerSignatures(*managerProcess);
        auto managerOffsets = new ManagerOffsets(*managerProcess, *managerSignatures);
        auto managerGame = new ManagerGame(*managerProcess);

        mManagers = {managerProcess, managerSignatures, managerOffsets, managerGame};

        Initialize();
    }

    ~Context()
    {
        std::apply([](auto &&...aArgs) { (delete aArgs, ...); }, mManagers);
    }

    int Run()
    {
        while (true)
        {
            // Update EntityList Entry
            GetManagerGame().UpdateEntityListEntry();

            DWORD64 LocalControllerAddress = 0;
            DWORD64 LocalPawnAddress = 0;

            if (!GetManagerProcess().ReadMemory(GetManagerGame().GetLocalControllerAddress(), LocalControllerAddress))
                continue;
            if (!GetManagerProcess().ReadMemory(GetManagerGame().GetLocalPawnAddress(), LocalPawnAddress))
                continue;

            // LocalEntity
            CEntity LocalEntity(GetManagerProcess(), GetManagerGame());
            static int LocalPlayerControllerIndex = 1;
            if (!LocalEntity.UpdateController(LocalControllerAddress))
                continue;
            if (!LocalEntity.UpdatePawn(LocalPawnAddress))
                continue;

            // AimBot data
            for (int i = 0; i < 64; i++)
            {
                CEntity Entity(GetManagerProcess(), GetManagerGame());
                DWORD64 EntityAddress = 0;
                if (!GetManagerProcess().ReadMemory<DWORD64>(GetManagerGame().GetEntityListEntry() + (i + 1) * 0x78,
                                                             EntityAddress))
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
            GetManagerProcess().WriteMemory(LocalEntity.Pawn.Address + Offsets::Entity::flFlashDuration, duration);
        }

        return 0;
    }

  private:
    void Initialize()
    {
        std::apply([](auto &&...aArgs) { (static_cast<IManager *>(aArgs)->Initialize(), ...); }, mManagers);
    }
};
