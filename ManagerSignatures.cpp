#include "pch.h"
#include "ManagerSignatures.h"
#include "ManagerProcess.h"

void SearchMemoryBlock(ManagerProcess &aManagerProcess, unsigned char *MemoryBuffer,
                       const std::vector<short> &NextArray, const std::vector<WORD> &SignatureArray,
                       DWORD64 StartAddress, DWORD64 Size, std::vector<DWORD64> &ResultArray)
{
    if (!aManagerProcess.ReadMemory(StartAddress, *MemoryBuffer, (int)Size))
        return;

    auto SignatureLength = SignatureArray.size();

    for (int i = 0, j, k; i < Size;)
    {
        j = i;
        k = 0;

        for (; k < SignatureLength && j < Size && (SignatureArray[k] == MemoryBuffer[j] || SignatureArray[k] == 256);
             k++, j++)
            ;

        if (k == SignatureLength)
            ResultArray.push_back(StartAddress + i);

        if ((i + SignatureLength) >= Size)
            return;

        int Num = NextArray[MemoryBuffer[i + SignatureLength]];
        if (Num == -1)
            i += ((int)SignatureLength - NextArray[256]);
        else
            i += ((int)SignatureLength - Num);
    }
}

std::vector<uintptr_t> SearchMemory(ManagerProcess &aManagerProcess, HANDLE mProcess, const std::string &Signature,
                                    uintptr_t StartAddress, uintptr_t EndAddress, int SearchNum)
{
    static const DWORD BLOCKMAXSIZE = 409600;

    std::vector<DWORD64> ResultArray;
    std::vector<WORD> SignatureArray;
    std::vector<short> NextArray(260, -1);

    unsigned char *MemoryBuffer = new unsigned char[BLOCKMAXSIZE];

    if (GetSignatureArray(Signature, SignatureArray) <= 0)
        return ResultArray;

    GetNextArray(NextArray, SignatureArray);

    MEMORY_BASIC_INFORMATION mbi;
    int Count;
    while (VirtualQueryEx(mProcess, reinterpret_cast<LPCVOID>(StartAddress), &mbi, sizeof(mbi)) != 0)
    {
        Count = 0;
        auto BlockSize = (DWORD64)mbi.RegionSize;

        while (BlockSize >= BLOCKMAXSIZE)
        {
            if (ResultArray.size() >= SearchNum)
                goto END;

            SearchMemoryBlock(aManagerProcess, MemoryBuffer, NextArray, SignatureArray,
                              StartAddress + (BLOCKMAXSIZE * Count), BLOCKMAXSIZE, ResultArray);

            BlockSize -= BLOCKMAXSIZE;
            Count++;
        }

        SearchMemoryBlock(aManagerProcess, MemoryBuffer, NextArray, SignatureArray,
                          StartAddress + (BLOCKMAXSIZE * Count), BlockSize, ResultArray);

        StartAddress += mbi.RegionSize;

        if (ResultArray.size() >= SearchNum || EndAddress != 0 && StartAddress > EndAddress)
            break;
    }

END:

    delete[] MemoryBuffer;
    return ResultArray;
}
