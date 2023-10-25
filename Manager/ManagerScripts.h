#pragma once

#include "IManager.h"
#include "Script/ScriptAntiFB.h"

class ManagerScripts : public IManager
{
  public:
    ManagerScripts(ManagerProcess &aManagerProcess, EntityLocal &aEntityLocal);

    constexpr void Update()
    {
        std::apply([](auto &&...aArgs) { (static_cast<IScript *>(aArgs)->Update(), ...); }, mScripts);
    }

  private:
    std::tuple<ScriptAntiFB *> mScripts{};
};
