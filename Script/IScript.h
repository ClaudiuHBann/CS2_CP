#pragma once

class IScript
{
    friend class ManagerScripts;

  protected:
    virtual void Update() = 0;
};
