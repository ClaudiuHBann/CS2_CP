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
    void Update() override;

  private:
    ManagerGame &mManagerGame;
    EntityLocal &mEntityLocal;
};
