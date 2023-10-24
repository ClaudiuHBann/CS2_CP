#pragma once

class IManager
{
    friend class Context;

  protected:
    virtual void Initialize() = 0;
};
