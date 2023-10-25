#pragma once

#include "IManager.h"

class ManagerProcess;
class ManagerSignatures;

class ManagerOffsets : public IManager
{
    ManagerProcess &mManagerProcess;
    ManagerSignatures &mManagerSignatures;

  public:
    constexpr ManagerOffsets(ManagerProcess &aManagerProcess, ManagerSignatures &aManagerSignatures) noexcept
        : mManagerProcess(aManagerProcess), mManagerSignatures(aManagerSignatures)
    {
    }

    [[nodiscard]] void Initialize() override;
};
