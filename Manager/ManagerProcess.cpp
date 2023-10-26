#include "pch.h"
#include "ManagerProcess.h"

ManagerProcess::~ManagerProcess() noexcept
{
    Detach();
}

bool ManagerProcess::Attach(const std::wstring &aProcessName) noexcept
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

void ManagerProcess::Detach() noexcept
{
    if (mProcess)
    {
        CloseHandle(mProcess);
    }
    mProcess = {};

    mAttached = {};
    mPID = {};
}

/* [[nodiscard]] */ std::uintptr_t ManagerProcess::TraceAddress(std::uintptr_t aBase,
                                                                std::vector<std::ptrdiff_t> aOffsets)
{
    std::uintptr_t Address = 0;

    if (aOffsets.size() == 0)
        return aBase;

    if (!ReadMemory<std::uintptr_t>(aBase, Address))
        return 0;

    for (int i = 0; i < aOffsets.size() - 1; i++)
    {
        if (!ReadMemory<std::uintptr_t>(Address + aOffsets[i], Address))
            return 0;
    }
    return Address == 0 ? 0 : Address + aOffsets[aOffsets.size() - 1];
}

void ManagerProcess::Initialize()
{
    Attach(L"cs2.exe");
}

/* [[nodiscard]] static */ uint32_t ManagerProcess::GetProcessID(const std::wstring &aProcessName) noexcept
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

/* [[nodiscard]] static */ Module ManagerProcess::GetProcessModule(const uint32_t aPID,
                                                                   const std::wstring &aModuleName) noexcept
{
    MODULEENTRY32W entry{.dwSize = sizeof(entry)};

    const auto ss = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, aPID);
    Module32FirstW(ss, &entry);
    do
    {
        if (!aModuleName.compare(entry.szModule))
        {
            CloseHandle(ss);
            return {reinterpret_cast<std::uintptr_t>(entry.hModule), entry.modBaseSize};
        }
    } while (Module32NextW(ss, &entry));

    CloseHandle(ss);
    return {};
}
