#pragma once

#include "Manager/ManagerGame.h"
#include "Manager/ManagerProcess.h"
#include "Pawn.h"

class Controller
{
    DEFINE_BASE;

  public:
    constexpr Controller(ManagerProcess &aManagerProcess, ManagerGame &aManagerGame, Pawn &aPawn) noexcept
        : mManagerProcess(aManagerProcess), mManagerGame(aManagerGame), mPawn(aPawn)
    {
    }

    [[nodiscard]] inline std::uintptr_t FindPawnAddress() const
    {
        mPawn.Base(mManagerProcess.ReadMemory<std::uintptr_t>(mBase + Offsets::hPlayerPawn));

        // TODO: wtf are those magic numbers?
        auto entityListEntry = mManagerProcess.ReadMemory<std::uintptr_t>(mManagerGame.GetEntityList() + 0x10 +
                                                                          8 * ((mPawn.Base() & 0x7FFF) >> 9));
        return mManagerProcess.ReadMemory<std::uintptr_t>(entityListEntry + 0x78 * (mPawn.Base() & 0x1FF));
    }

  private:
    ManagerProcess &mManagerProcess;
    ManagerGame &mManagerGame;
    Pawn &mPawn;
};
