#pragma once

#include "IManager.h"

class ManagerProcess;

class ManagerSignatures : public IManager
{
  public:
    constexpr ManagerSignatures(ManagerProcess &aManagerProcess) noexcept : mManagerProcess(aManagerProcess)
    {
    }

    void FindSignatures(const Module &aModule, const std::vector<std::ptrdiff_t *> &aOffsets,
                        const std::vector<Signature> &aSignatures) const noexcept;

  private:
    ManagerProcess &mManagerProcess;

    [[nodiscard]] std::uintptr_t FindSignature(const std::vector<std::uint8_t> &aData, const Module &aModule,
                                               const Signature &aSignature) const noexcept;

    [[nodiscard]] static std::vector<std::int16_t> SignatureToBytes(std::wstring aSignature) noexcept;

    [[nodiscard]] static std::ptrdiff_t FindOffset(const std::vector<std::uint8_t> &aData,
                                                   const std::wstring &aSignature) noexcept;
};
