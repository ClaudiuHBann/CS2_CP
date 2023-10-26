#pragma once

#include "IScript.h"

class ManagerProcess;
class ManagerGame;

class ScriptRadar : public IScript
{
  public:
    constexpr ScriptRadar(ManagerProcess &aManagerProcess, ManagerGame &aManagerGame) noexcept
        : mManagerProcess(aManagerProcess), mManagerGame(aManagerGame)
    {
    }

  protected:
    void Update() override;

  private:
    ManagerProcess &mManagerProcess;
    ManagerGame &mManagerGame;
};
