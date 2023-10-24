#include "pch.h"
#include "ManagerSignatures.h"

std::uintptr_t SearchMemory(const char *signature, void *module, size_t size)
{
    static auto pattern_to_byte = [](const char *pattern) {
        auto bytes = std::vector<int>{};
        auto start = const_cast<char *>(pattern);
        auto end = const_cast<char *>(pattern) + strlen(pattern);

        for (auto current = start; current < end; ++current)
        {
            if (*current == '?')
            {
                ++current;
                if (*current == '?')
                    ++current;
                bytes.push_back(-1);
            }
            else
            {
                bytes.push_back(strtoul(current, &current, 16));
            }
        }
        return bytes;
    };

    auto patternBytes = pattern_to_byte(signature);
    auto scanBytes = reinterpret_cast<std::uint8_t *>(module);

    auto s = patternBytes.size();
    auto d = patternBytes.data();

    for (auto i = 0ul; i < size - s; ++i)
    {
        bool found = true;
        for (auto j = 0ul; j < s; ++j)
        {
            if (scanBytes[i + j] != d[j] && d[j] != -1)
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
