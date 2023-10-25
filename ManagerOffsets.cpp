#include "pch.h"
#include "ManagerOffsets.h"
#include "ManagerProcess.h"
#include "ManagerSignatures.h"
#include "Offsets.h"
#include "Signatures.h"

/* [[nodiscard]] */ void ManagerOffsets::Initialize()
{
    const auto &moduleClientDLL = mManagerProcess.GetModuleClient();
    if (!moduleClientDLL.mBase)
    {
        return;
    }

    std::vector<std::ptrdiff_t *> offsets{&Offsets::dwForceJump, &Offsets::dwEntityList,
                                          &Offsets::dwLocalPlayerController, &Offsets::dwLocalPlayerPawn};

    std::vector<Signature> signatures{Signatures::dwForceJump, Signatures::dwEntityList,
                                      Signatures::dwLocalPlayerController, Signatures::dwLocalPlayerPawn};

    mManagerSignatures.FindSignatures(moduleClientDLL, offsets, signatures);
}
