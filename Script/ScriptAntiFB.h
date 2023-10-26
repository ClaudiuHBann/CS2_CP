#pragma once

#include "Entity/EntityLocal.h"
#include "IScript.h"

class ScriptAntiFB : public IScript
{
  public:
    constexpr ScriptAntiFB(ManagerProcess &aManagerProcess, EntityLocal &aEntityLocal) noexcept
        : mManagerProcess(aManagerProcess), mEntityLocal(aEntityLocal)
    {
    }

  protected:
    inline void Update() override
    {
        mManagerProcess.WriteMemory(mEntityLocal.GetPawn().Base() + Offsets::Entity::flFlashDuration, 0.f);
    }

  private:
    ManagerProcess &mManagerProcess;
    EntityLocal &mEntityLocal;
};
