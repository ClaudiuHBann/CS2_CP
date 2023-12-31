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
        mEntity.UpdatePawn(mManagerGame.GetLocalPawn());
    }

    [[nodiscard]] constexpr Pawn &GetPawn() noexcept
    {
        return mEntity.GetPawn();
    }

  private:
    ManagerGame &mManagerGame;
    Entity mEntity;
};
