#include "pch.h"
#include "ManagerSignatures.h"
#include "ManagerProcess.h"

/* [[nodiscard]] static */ std::vector<std::int16_t> ManagerSignatures::SignatureToBytes(
    std::wstring aSignature) noexcept
{
    std::vector<std::int16_t> bytes{};

    for (auto current = aSignature.data(); current < aSignature.data() + aSignature.size(); ++current)
    {
        std::int16_t byte{};
        if (*current == '?')
        {
            if (*++current == '?')
            {
                current++;
            }

            byte = -1;
        }
        else
        {
            byte = static_cast<std::int16_t>(wcstoul(current, &current, 16));
        }

        bytes.push_back(byte);
    }

    return bytes;
}

/* [[nodiscard]] static */ std::ptrdiff_t ManagerSignatures::FindOffset(const std::vector<std::uint8_t> &aData,
                                                                        const std::wstring &aSignature) noexcept
{
    auto signatureAsBytes = SignatureToBytes(aSignature);
    for (std::size_t i = 0; i < aData.size() - signatureAsBytes.size(); i++)
    {
        bool found = true;
        for (std::size_t j = 0; j < signatureAsBytes.size(); j++)
        {
            if (aData[i + j] != signatureAsBytes[j] && signatureAsBytes[j] != -1)
            {
                found = false;
                break;
            }
        }

        if (found)
        {
            return i;
        }
    }

    return {};
}

/* [[nodiscard]] */ std::uintptr_t ManagerSignatures::FindSignature(const std::vector<std::uint8_t> &aData,
                                                                    const Module &aModule,
                                                                    const Signature &aSignature) const noexcept
{
    auto address = aModule.mBase + FindOffset(aData, aSignature.mPattern);

    // TODO: is this shit for client.dll only?
    uint32_t offset{};
    mManagerProcess.ReadMemory(address + 3, offset);
    address += offset + 7;

    return address - aModule.mBase + aSignature.mOffset;
}

void ManagerSignatures::FindSignatures(const Module &aModule, const std::vector<std::ptrdiff_t *> &aOffsets,
                                       const std::vector<Signature> &aSignatures) const noexcept
{
    if (aOffsets.size() != aSignatures.size())
    {
        return;
    }

    std::vector<std::uint8_t> data(aModule.mSize);
    mManagerProcess.ReadMemory(aModule.mBase, *data.data(), data.size());

    for (size_t i = 0; i < aSignatures.size(); i++)
    {
        *aOffsets[i] = FindSignature(data, aModule, aSignatures[i]);
    }
}
