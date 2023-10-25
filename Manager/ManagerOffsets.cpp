#include "pch.h"
#include "ManagerOffsets.h"
#include "ManagerProcess.h"
#include "ManagerSignatures.h"

/* [[nodiscard]] */ void ManagerOffsets::Initialize()
{
    const auto &moduleClientDLL = mManagerProcess.GetModuleClient();
    if (!moduleClientDLL.mBase)
    {
        return;
    }

    std::vector<std::ptrdiff_t *> offsets{&Offsets::dwForceJump, &Offsets::dwEntityList,
                                          &Offsets::dwLocalController, &Offsets::dwLocalPawn};

    std::vector<Signature> signatures{Signatures::dwForceJump, Signatures::dwEntityList,
                                      Signatures::dwLocalController, Signatures::dwLocalPawn};

    mManagerSignatures.FindSignatures(moduleClientDLL, offsets, signatures);
}
