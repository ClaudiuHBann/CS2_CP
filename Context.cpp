#include "pch.h"
#include "Context.h"

Context::Context()
{
    auto managerProcess = new ManagerProcess;
    auto managerSignatures = new ManagerSignatures(*managerProcess);
    auto managerOffsets = new ManagerOffsets(*managerProcess, *managerSignatures);
    auto managerGame = new ManagerGame(*managerProcess);

    mManagers = {managerProcess, managerSignatures, managerOffsets, managerGame};

    Initialize();
}

Context ::~Context()
{
    std::apply([](auto &&...aArgs) { (delete aArgs, ...); }, mManagers);
}

void Context::Initialize()
{
    std::apply([](auto &&...aArgs) { (static_cast<IManager *>(aArgs)->Initialize(), ...); }, mManagers);
}
