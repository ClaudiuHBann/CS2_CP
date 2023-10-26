#pragma once

#include "ManagerProcess.h"

class ManagerGame : public IManager
{
  public:
    constexpr ManagerGame(ManagerProcess &aManagerProcess) noexcept : mManagerProcess(aManagerProcess)
    {
    }

    void Initialize() override;

    bool SetForceJump(const int aValue) const;

    [[nodiscard]] inline auto GetEntityList() const
    {
        return mManagerProcess.ReadMemory<std::uintptr_t>(mEntityList);
    }

    [[nodiscard]] inline auto GetLocalController() const
    {
        return mManagerProcess.ReadMemory<std::uintptr_t>(mLocalController);
    }

    [[nodiscard]] inline auto GetLocalPawn() const
    {
        return mManagerProcess.ReadMemory<std::uintptr_t>(mLocalPawn);
    }

  private:
    ManagerProcess &mManagerProcess;

    std::uintptr_t mForceJump{};

    std::uintptr_t mEntityList{};

    std::uintptr_t mLocalPawn{};
    std::uintptr_t mLocalController{};
};
