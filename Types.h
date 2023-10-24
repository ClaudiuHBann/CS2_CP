#pragma once

class Vector2f
{
  public:
    Vector2f(const float aX = {}, const float aY = {}) : mX(aX), mY(aY)
    {
    }

  private:
    float mX{};
    float mY{};
};

struct Module
{
    uintptr_t mBase{};
    size_t mSize{};
};

struct Signature
{
    const wchar_t *mPattern{};
    std::ptrdiff_t mOffset{};
};
