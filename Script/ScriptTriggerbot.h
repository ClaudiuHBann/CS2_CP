#pragma once

#include "Entity/EntityLocal.h"
#include "IScript.h"

class ScriptTriggerbot : public IScript
{
  public:
    constexpr ScriptTriggerbot(ManagerProcess &aManagerProcess, ManagerGame &aManagerGame,
                               EntityLocal &aEntityLocal) noexcept
        : mManagerProcess(aManagerProcess), mManagerGame(aManagerGame), mEntityLocal(aEntityLocal)
    {
    }

  protected:
    void Update() override;

  private:
    ManagerProcess &mManagerProcess;
    ManagerGame &mManagerGame;
    EntityLocal &mEntityLocal;
};
