#include "pch.h"
#include "ManagerScripts.h"

ManagerScripts::ManagerScripts(ManagerProcess &aManagerProcess, ManagerGame &aManagerGame, EntityLocal &aEntityLocal)
{
    auto scriptAntiFB = new ScriptAntiFB(aManagerProcess, aEntityLocal);
    auto scriptBhop = new ScriptBhop(aManagerGame, aEntityLocal);
    auto scriptRadar = new ScriptRadar(aManagerProcess, aManagerGame);
    auto scriptTriggerbot = new ScriptTriggerbot(aManagerProcess, aManagerGame, aEntityLocal);

    mScripts = {scriptAntiFB, scriptBhop, scriptRadar, scriptTriggerbot};
}
