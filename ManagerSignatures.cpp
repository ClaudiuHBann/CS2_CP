#include "pch.h"
#include "ManagerSignatures.h"
#include "ManagerProcess.h"

void SearchMemoryBlock(::byte *MemoryBuffer, const std::vector<short> &NextArray,
                       const std::vector<WORD> &SignatureArray, DWORD64 StartAddress, DWORD64 Size,
                       std::vector<DWORD64> &ResultArray)
{
    if (!ProcessManager::ReadMemory(StartAddress, *MemoryBuffer, (int)Size))
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
