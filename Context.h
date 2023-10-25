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
    Context();
    ~Context();

    int Run()
    {
        while (true)
        {
            auto LocalControllerAddress =
                GetManagerProcess().ReadMemory<std::uintptr_t>(GetManagerGame().GetLocalControllerAddress());
            auto LocalPawnAddress =
                GetManagerProcess().ReadMemory<std::uintptr_t>(GetManagerGame().GetLocalPawnAddress());

            // LocalEntity
            CEntity LocalEntity(GetManagerProcess(), GetManagerGame());
            if (!LocalEntity.UpdateController(LocalControllerAddress))
                continue;
            LocalEntity.UpdatePawn(LocalPawnAddress);

            float duration{};
            GetManagerProcess().WriteMemory(LocalEntity.Pawn.Base() + Offsets::Entity::flFlashDuration, duration);
        }

        return 0;
    }

  private:
    void Initialize();
};
