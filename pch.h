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
#include "Types.h"

/*
    TODO:
         - add tracing
         - remove std from uintptr_t and size_t and ptrdiff_t
         - IScript base class with pure virtual func Run with ScriptAntiFlashbang and a ManagerScripts
*/
