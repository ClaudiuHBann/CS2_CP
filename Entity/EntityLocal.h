#pragma once

#include "Entity.h"

class EntityLocal
{
  public:
    constexpr EntityLocal(ManagerProcess &aManagerProcess, ManagerGame &aManagerGame) noexcept
        : mManagerGame(aManagerGame), mEntity(aManagerProcess, mManagerGame)
    {
    }

    inline void Update()
    {
        mEntity.UpdatePawn();
    }

    [[nodiscard]] constexpr Entity &GetEntity() noexcept
    {
        return mEntity;
    }

  private:
    ManagerGame &mManagerGame;
    Entity mEntity;
};
