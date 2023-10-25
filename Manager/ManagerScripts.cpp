#include "pch.h"
#include "ManagerScripts.h"

ManagerScripts::ManagerScripts(ManagerProcess &aManagerProcess, EntityLocal &aEntityLocal)
{
    auto scriptAntiFB = new ScriptAntiFB(aManagerProcess, aEntityLocal);

    mScripts = {scriptAntiFB};
}
