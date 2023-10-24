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
