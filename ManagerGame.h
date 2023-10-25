#pragma once

#include "IManager.h"

class ManagerProcess;

class ManagerGame : public IManager
{
  public:
    constexpr ManagerGame(ManagerProcess &aManagerProcess) noexcept : mManagerProcess(aManagerProcess)
    {
    }

    void Initialize() override;

    [[nodiscard]] constexpr auto GetForceJumpAddress() const noexcept
    {
        return mForceJump;
    }

    bool SetForceJump(const int aValue) const;

    [[nodiscard]] constexpr auto GetEntityListAddress() const noexcept
    {
        return mEntityList;
    }

    [[nodiscard]] std::uintptr_t GetEntityListEntryAddress();

    [[nodiscard]] constexpr auto GetLocalPawnAddress() const noexcept
    {
        return mLocalPawn;
    }

    [[nodiscard]] constexpr auto GetLocalControllerAddress() const noexcept
    {
        return mLocalController;
    }

  private:
    ManagerProcess &mManagerProcess;

    std::uintptr_t mForceJump{};

    std::uintptr_t mEntityList{};
    std::uintptr_t mEntityListEntry{};

    std::uintptr_t mLocalPawn{};
    std::uintptr_t mLocalController{};
};
