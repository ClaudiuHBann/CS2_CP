#pragma once

#include "ManagerSignatures.h"

static inline const DWORD BLOCKMAXSIZE = 409600;

class ProcessManager
{
  private:
    static inline bool Attached = false;

  public:
    static inline HANDLE hProcess = 0;
    static inline DWORD ProcessID = 0;
    static inline DWORD64 ModuleAddress = 0;

  public:
    ~ProcessManager()
    {
        // if (hProcess)
        // CloseHandle(hProcess);
    }

    static bool Attach(std::string ProcessName)
    {
        ProcessID = GetProcessID(ProcessName);
        hProcess = OpenProcess(PROCESS_ALL_ACCESS | PROCESS_CREATE_THREAD, TRUE, ProcessID);
        ModuleAddress = reinterpret_cast<DWORD64>(GetProcessModuleHandle(ProcessName));

        Attached = true;
        return true;
    }

    static void Detach()
    {
        if (hProcess)
            CloseHandle(hProcess);
        hProcess = 0;
        ProcessID = 0;
        ModuleAddress = 0;
        Attached = false;
    }

    static bool IsActive()
    {
        if (!Attached)
            return false;
        DWORD ExitCode{};
        GetExitCodeProcess(hProcess, &ExitCode);
        return ExitCode == STILL_ACTIVE;
    }

    template <typename ReadType> static bool ReadMemory(DWORD64 Address, ReadType &Value, int Size)
    {
        if (ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(Address), &Value, Size, 0))
            return true;
        return false;
    }

    template <typename ReadType> static bool ReadMemory(DWORD64 Address, ReadType &Value)
    {
        if (ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(Address), &Value, sizeof(ReadType), 0))
            return true;
        return false;
    }

    template <typename ReadType> static bool WriteMemory(DWORD64 Address, ReadType &Value, int Size)
    {
        if (WriteProcessMemory(hProcess, reinterpret_cast<LPCVOID>(Address), &Value, Size, 0))
            return true;
        return false;
    }

    template <typename ReadType> static bool WriteMemory(DWORD64 Address, ReadType &Value)
    {
        if (WriteProcessMemory(hProcess, reinterpret_cast<LPVOID>(Address), &Value, sizeof(ReadType), 0))
            return true;
        return false;
    }

    static std::vector<DWORD64> SearchMemory(const std::string &Signature, DWORD64 StartAddress, DWORD64 EndAddress,
                                             int SearchNum = 1)
    {
        std::vector<DWORD64> ResultArray;
        std::vector<WORD> SignatureArray;
        std::vector<short> NextArray(260, -1);

        ::byte *MemoryBuffer = new ::byte[BLOCKMAXSIZE];

        if (GetSignatureArray(Signature, SignatureArray) <= 0)
            return ResultArray;

        GetNextArray(NextArray, SignatureArray);

        MEMORY_BASIC_INFORMATION mbi;
        int Count;
        while (VirtualQueryEx(hProcess, reinterpret_cast<LPCVOID>(StartAddress), &mbi, sizeof(mbi)) != 0)
        {
            Count = 0;
            auto BlockSize = (DWORD64)mbi.RegionSize;

            while (BlockSize >= BLOCKMAXSIZE)
            {
                if (ResultArray.size() >= SearchNum)
                    goto END;

                SearchMemoryBlock(MemoryBuffer, NextArray, SignatureArray, StartAddress + (BLOCKMAXSIZE * Count),
                                  BLOCKMAXSIZE, ResultArray);

                BlockSize -= BLOCKMAXSIZE;
                Count++;
            }

            SearchMemoryBlock(MemoryBuffer, NextArray, SignatureArray, StartAddress + (BLOCKMAXSIZE * Count), BlockSize,
                              ResultArray);

            StartAddress += mbi.RegionSize;

            if (ResultArray.size() >= SearchNum || EndAddress != 0 && StartAddress > EndAddress)
                break;
        }

    END:

        delete[] MemoryBuffer;
        return ResultArray;
    }

    static DWORD64 TraceAddress(DWORD64 BaseAddress, std::vector<DWORD> Offsets)
    {
        DWORD64 Address = 0;

        if (Offsets.size() == 0)
            return BaseAddress;

        if (!ReadMemory<DWORD64>(BaseAddress, Address))
            return 0;

        for (int i = 0; i < Offsets.size() - 1; i++)
        {
            if (!ReadMemory<DWORD64>(Address + Offsets[i], Address))
                return 0;
        }
        return Address == 0 ? 0 : Address + Offsets[Offsets.size() - 1];
    }

  public:
    static DWORD GetProcessID(std::string ProcessName)
    {
        PROCESSENTRY32 ProcessInfoPE;
        ProcessInfoPE.dwSize = sizeof(PROCESSENTRY32);
        HANDLE hSnapshot = CreateToolhelp32Snapshot(15, 0);
        Process32First(hSnapshot, &ProcessInfoPE);
        USES_CONVERSION;
        do
        {
            if (strcmp(W2A(ProcessInfoPE.szExeFile), ProcessName.c_str()) == 0)
            {
                CloseHandle(hSnapshot);
                return ProcessInfoPE.th32ProcessID;
            }
        } while (Process32Next(hSnapshot, &ProcessInfoPE));
        CloseHandle(hSnapshot);
        return 0;
    }

    static HMODULE GetProcessModuleHandle(std::string ModuleName)
    {
        MODULEENTRY32 ModuleInfoPE;
        ModuleInfoPE.dwSize = sizeof(MODULEENTRY32);
        HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, ProcessID);
        Module32First(hSnapshot, &ModuleInfoPE);
        USES_CONVERSION;
        do
        {
            if (strcmp(W2A(ModuleInfoPE.szModule), ModuleName.c_str()) == 0)
            {
                CloseHandle(hSnapshot);
                return ModuleInfoPE.hModule;
            }
        } while (Module32Next(hSnapshot, &ModuleInfoPE));
        CloseHandle(hSnapshot);
        return 0;
    }
};
