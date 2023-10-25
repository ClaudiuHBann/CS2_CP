#pragma once

class Vector2f
{
  public:
    constexpr Vector2f(const float aX = {}, const float aY = {}) noexcept : mX(aX), mY(aY)
    {
    }

    float mX{};
    float mY{};
};

struct Module
{
    std::uintptr_t mBase{};
    std::size_t mSize{};
};

struct Signature
{
    const wchar_t *mPattern{};
    std::ptrdiff_t mOffset{};
};
