#pragma once

#include "ManagerSignatures.h"

class ManagerProcess
{
  public:
    struct Module
    {
        uintptr_t mBase{};
        size_t mSize{};
    };

    inline ~ManagerProcess() noexcept
    {
        Detach();
    }

    inline bool Attach(const std::wstring &aProcessName) noexcept
    {
        mPID = GetProcessID(aProcessName);
        if (!mPID)
        {
            return false;
        }

        mProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, mPID);
        if (!mProcess)
        {
            return false;
        }

        mModuleClient = GetProcessModule(mPID, L"client.dll");
        if (!mModuleClient.mBase || !mModuleClient.mSize)
        {
            return false;
        }

        return mAttached = true;
    }

    inline void Detach() noexcept
    {
        if (mProcess)
        {
            CloseHandle(mProcess);
        }
        mProcess = {};

        mAttached = {};
        mPID = {};
    }

    template <typename ReadType> bool ReadMemory(uintptr_t Address, ReadType &Value, int Size)
    {
        return ReadProcessMemory(mProcess, reinterpret_cast<LPCVOID>(Address), &Value, Size, 0);
    }

    template <typename ReadType> bool ReadMemory(uintptr_t Address, ReadType &Value)
    {
        if (ReadProcessMemory(mProcess, reinterpret_cast<LPCVOID>(Address), &Value, sizeof(ReadType), 0))
            return true;
        return false;
    }

    template <typename ReadType> bool WriteMemory(uintptr_t Address, ReadType &Value, int Size)
    {
        if (WriteProcessMemory(mProcess, reinterpret_cast<LPCVOID>(Address), &Value, Size, 0))
            return true;
        return false;
    }

    template <typename ReadType> bool WriteMemory(uintptr_t Address, ReadType &Value)
    {
        if (WriteProcessMemory(mProcess, reinterpret_cast<LPVOID>(Address), &Value, sizeof(ReadType), 0))
            return true;
        return false;
    }

    [[nodiscard]] constexpr const Module &GetModuleClient() const noexcept
    {
        return mModuleClient;
    }

    [[nodiscard]] constexpr HANDLE GetProcess() const noexcept
    {
        return mProcess;
    }

  private:
    HANDLE mProcess{};
    uint32_t mPID{};

    Module mModuleClient{};

    bool mAttached{};

    [[nodiscard]] static uint32_t GetProcessID(const std::wstring &aProcessName) noexcept
    {
        PROCESSENTRY32W entry{.dwSize = sizeof(entry)};

        const auto ss = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        Process32FirstW(ss, &entry);
        do
        {
            if (!aProcessName.compare(entry.szExeFile))
            {
                CloseHandle(ss);
                return entry.th32ProcessID;
            }
        } while (Process32NextW(ss, &entry));

        CloseHandle(ss);
        return {};
    }

    [[nodiscard]] static Module GetProcessModule(const uint32_t aPID, const std::wstring &aModuleName) noexcept
    {
        MODULEENTRY32W entry{.dwSize = sizeof(entry)};

        const auto ss = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, aPID);
        Module32FirstW(ss, &entry);
        do
        {
            if (!aModuleName.compare(entry.szModule))
            {
                CloseHandle(ss);
                return {reinterpret_cast<uintptr_t>(entry.hModule), entry.modBaseSize};
            }
        } while (Module32NextW(ss, &entry));

        CloseHandle(ss);
        return {};
    }
};
