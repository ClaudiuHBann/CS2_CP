#include "pch.h"
#include "Context.h"

Context::Context()
{
    auto managerProcess = new ManagerProcess;
    auto managerSignatures = new ManagerSignatures(*managerProcess);
    auto managerOffsets = new ManagerOffsets(*managerProcess, *managerSignatures);
    auto managerGame = new ManagerGame(*managerProcess);
    mEntityLocal = new EntityLocal(*managerProcess, *managerGame);
    auto managerScripts = new ManagerScripts(*managerProcess, *managerGame, *mEntityLocal);

    mManagers = {managerProcess, managerSignatures, managerOffsets, managerGame, managerScripts};

    Initialize();
}
