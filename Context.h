#pragma once

#include "Entity/EntityLocal.h"
#include "Manager/ManagerOffsets.h"
#include "Manager/ManagerScripts.h"
#include "Manager/ManagerSignatures.h"

class Context
{
    std::tuple<ManagerProcess *, ManagerSignatures *, ManagerOffsets *, ManagerGame *, ManagerScripts *> mManagers{};

    [[nodiscard]] constexpr decltype(auto) GetManagerScripts() noexcept
    {
        return *std::get<ManagerScripts *>(mManagers);
    }

  public:
    Context();

    constexpr ~Context()
    {
        std::apply([](auto &&...aArgs) { (delete aArgs, ...); }, mManagers);
    }

    void Run()
    {
        while (true)
        {
            mEntityLocal->Update();
            GetManagerScripts().Update();
        }
    }

  private:
    EntityLocal *mEntityLocal{};

    constexpr void Initialize()
    {
        std::apply([](auto &&...aArgs) { (static_cast<IManager *>(aArgs)->Initialize(), ...); }, mManagers);
    }
};
