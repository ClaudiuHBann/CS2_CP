#pragma once

class IManager
{
    friend class Context;

  protected:
    virtual constexpr void Initialize()
    {
    }
};
