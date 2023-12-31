#pragma once

#include "IManager.h"

class ManagerProcess : public IManager
{
  public:
    ~ManagerProcess() noexcept;

    bool Attach(const std::wstring &aProcessName) noexcept;
    void Detach() noexcept;

    template <typename Type>
    inline bool ReadMemory(const std::uintptr_t aAddress, Type &aData, const std::size_t aSize = sizeof(Type))
    {
        return ReadProcessMemory(mProcess, reinterpret_cast<LPCVOID>(aAddress), &aData, aSize, 0);
    }

    template <typename Type> inline Type ReadMemory(const std::uintptr_t aAddress)
    {
        Type data{};
        ReadMemory(aAddress, data);
        return data;
    }

    template <typename Type>
    inline bool WriteMemory(const std::uintptr_t aAddress, const Type &aData, const std::size_t aSize = sizeof(Type))
    {
        return WriteProcessMemory(mProcess, reinterpret_cast<LPVOID>(aAddress), &aData, aSize, 0);
    }

    [[nodiscard]] inline auto TraceAddress(const std::uintptr_t aBase, const std::ptrdiff_t aOffset)
    {
        return ReadMemory<std::uintptr_t>(ReadMemory<std::uintptr_t>(aBase) + aOffset);
    }

    [[nodiscard]] constexpr const Module &GetModuleClient() const noexcept
    {
        return mModuleClient;
    }

    [[nodiscard]] constexpr HANDLE GetProcess() const noexcept
    {
        return mProcess;
    }

  protected:
    void Initialize() override;

  private:
    HANDLE mProcess{};
    uint32_t mPID{};

    Module mModuleClient{};

    bool mAttached{};

    [[nodiscard]] static uint32_t GetProcessID(const std::wstring &aProcessName) noexcept;
    [[nodiscard]] static Module GetProcessModule(const uint32_t aPID, const std::wstring &aModuleName) noexcept;
};
