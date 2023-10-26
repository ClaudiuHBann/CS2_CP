#include "pch.h"
#include "ScriptRadar.h"
#include "Entity/Entity.h"

void ScriptRadar::Update()
{
    // TODO: decipher this bs
    for (std::size_t i = 1; i <= 10; i++)
    {
        std::uintptr_t list_entry =
            mManagerProcess.ReadMemory<std::uintptr_t>(mManagerGame.GetEntityList() + (8 * (i & 0x7FFF) >> 9) + 16);
        if (!list_entry)
            continue;

        std::uintptr_t playerController = mManagerProcess.ReadMemory<std::uintptr_t>(list_entry + 120 * (i & 0x1FF));

        if (!playerController)
            continue;

        std::uint32_t playerPawn =
            mManagerProcess.ReadMemory<std::uint32_t>(playerController + Offsets::Entity::hPlayerPawn);

        if (!playerPawn)
            continue;

        std::uintptr_t list_entry2 = mManagerProcess.ReadMemory<std::uintptr_t>(mManagerGame.GetEntityList() +
                                                                                8 * ((playerPawn & 0x7FFF) >> 9) + 16);

        if (!list_entry)
            continue;

        std::uintptr_t pCSPlayerPawn =
            mManagerProcess.ReadMemory<std::uintptr_t>(list_entry2 + 120 * (playerPawn & 0x1FF));

        if (!pCSPlayerPawn)
            continue;

        mManagerProcess.WriteMemory(pCSPlayerPawn + Offsets::Entity::entitySpottedState + Offsets::Entity::bSpotted,
                                    true);
    }
}
