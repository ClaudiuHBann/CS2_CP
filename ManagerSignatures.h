#pragma once

static size_t GetSignatureArray(const std::string &Signature, std::vector<WORD> &SignatureArray)
{
    std::string Sig = Signature;
    Sig.erase(std::remove(Sig.begin(), Sig.end(), ' '), Sig.end());

    std::size_t Size = Sig.size();

    if (Size % 2 != 0)
        return 0;

    for (int i = 0; i < Size; i += 2)
    {
        std::string ByteString = Sig.substr(i, 2);
        WORD Byte = (ByteString == "??") ? 256 : (WORD)std::stoi(ByteString, nullptr, 16);
        SignatureArray.push_back(Byte);
    }
    return SignatureArray.size();
}

static void GetNextArray(std::vector<short> &NextArray, const std::vector<WORD> &SignatureArray)
{
    std::size_t Size = SignatureArray.size();
    for (size_t i = 0; i < Size; i++)
        NextArray[SignatureArray[i]] = (short)i;
}

void SearchMemoryBlock(::byte *MemoryBuffer, const std::vector<short> &NextArray,
                       const std::vector<WORD> &SignatureArray, DWORD64 StartAddress, DWORD64 Size,
                       std::vector<DWORD64> &ResultArray);
