#include "pch.h"
#include "ManagerScripts.h"

ManagerScripts::ManagerScripts(ManagerProcess &aManagerProcess, ManagerGame &aManagerGame, EntityLocal &aEntityLocal)
{
    auto scriptAntiFB = new ScriptAntiFB(aManagerProcess, aEntityLocal);
    auto scriptBhop = new ScriptBhop(aManagerGame, aEntityLocal);

    mScripts = {scriptAntiFB, scriptBhop};
}
