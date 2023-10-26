#pragma once

#include "IManager.h"
#include "Script/ScriptAntiFB.h"
#include "Script/ScriptBhop.h"

class ManagerScripts : public IManager
{
  public:
    ManagerScripts(ManagerProcess &aManagerProcess, ManagerGame &aManagerGame, EntityLocal &aEntityLocal);

    constexpr void Update()
    {
        std::apply([](auto &&...aArgs) { (static_cast<IScript *>(aArgs)->Update(), ...); }, mScripts);
    }

  private:
    std::tuple<ScriptAntiFB *, ScriptBhop *> mScripts{};
};
