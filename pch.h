#pragma once

// https://www.unknowncheats.me/forum/counter-strike-2-a/576077-counter-strike-2-reversal-structs-offsets-99.html

// win32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
// TlHelp32.h must be under Windows.h
#include <TlHelp32.h>

// std
#include <functional>
#include <string>
#include <vector>

// hbann
#include "Utility/Types.h"
// lower headers have dependencies on Types.h so:
#include "Utility/Offsets.h"
#include "Utility/Signatures.h"

// TODO: refactor these defines? (offsets and signatures too)
#define DEFINE_VAR(type, name)                                                                                         \
  private:                                                                                                             \
    type m##name{};

#define DEFINE_VAR_GET(parent, offset)                                                                                 \
  public:                                                                                                              \
    inline const decltype(m##offset) &offset(const bool aUpdate = true)                                                \
    {                                                                                                                  \
        if (aUpdate)                                                                                                   \
        {                                                                                                              \
            m##offset = mManagerProcess.ReadMemory<decltype(m##offset)>(Offsets::parent::offset);                      \
        }                                                                                                              \
                                                                                                                       \
        return m##offset;                                                                                              \
    }

#define DEFINE_VAR_SET(parent, offset)                                                                                 \
  public:                                                                                                              \
    inline decltype(auto) offset(const decltype(m##offset) &aValue)                                                    \
    {                                                                                                                  \
        m##offset = aValue;                                                                                            \
        mManagerProcess.WriteMemory(mBase + Offsets::parent::offset, m##offset);                                       \
        return *this;                                                                                                  \
    }

#define DEFINE_BASE                                                                                                    \
  private:                                                                                                             \
    std::uintptr_t mBase{};                                                                                            \
                                                                                                                       \
  public:                                                                                                              \
    [[nodiscard]] constexpr auto Base() noexcept                                                                       \
    {                                                                                                                  \
        return mBase;                                                                                                  \
    }                                                                                                                  \
                                                                                                                       \
    constexpr decltype(auto) Base(const decltype(mBase) &aValue) noexcept                                              \
    {                                                                                                                  \
        mBase = aValue;                                                                                                \
        return *this;                                                                                                  \
    }

#define DEFINE_VAR_GET_SET(type, name, parent)                                                                         \
    DEFINE_VAR(type, name)                                                                                             \
    DEFINE_VAR_GET(parent, name)                                                                                       \
    DEFINE_VAR_SET(parent, name)

/*
    TODO:
         - add tracing
         - add namespaces
         - IScript base class with pure virtual func Run with ScriptAntiFlashbang and a ManagerScripts
*/
