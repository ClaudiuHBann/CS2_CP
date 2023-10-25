#pragma once

#include "Entity/Entity.h"
#include "Manager/ManagerGame.h"
#include "Manager/ManagerOffsets.h"
#include "Manager/ManagerProcess.h"
#include "Manager/ManagerSignatures.h"

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

    void Run()
    {
        while (true)
        {
            Entity entityLocal(GetManagerProcess(), GetManagerGame());
            entityLocal.UpdateController(GetManagerGame().GetLocalController());
            entityLocal.UpdatePawn(GetManagerGame().GetLocalPawn());

            float duration{};
            GetManagerProcess().WriteMemory(entityLocal.GetPawn().Base() + Offsets::Entity::flFlashDuration, duration);
        }
    }

  private:
    void Initialize();
};
