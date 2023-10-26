#pragma once

#include "Entity/EntityLocal.h"
#include "IScript.h"

class ScriptBhop : public IScript
{
  public:
    constexpr ScriptBhop(ManagerGame &aManagerGame, EntityLocal &aEntityLocal) noexcept
        : mManagerGame(aManagerGame), mEntityLocal(aEntityLocal)
    {
    }

  protected:
    inline void Update() override
    {
        // TODO: explain magic numbers....
        const bool hasFlagInAir = mEntityLocal.GetEntity().GetPawn().HasFlag(Pawn::Flags::IN_AIR);
        if (GetAsyncKeyState(VK_SPACE) && hasFlagInAir)
        {
            mManagerGame.SetForceJump(65537);
        }
        else if (GetAsyncKeyState(VK_SPACE) && !hasFlagInAir)
        {
            mManagerGame.SetForceJump(256);
            mManagerGame.SetForceJump(65537);
            mManagerGame.SetForceJump(256);
        }
        else
        {
            mManagerGame.SetForceJump(256);
        }
    }

  private:
    ManagerGame &mManagerGame;
    EntityLocal &mEntityLocal;
};
