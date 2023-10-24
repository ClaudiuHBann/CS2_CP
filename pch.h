#pragma once

// win32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <Tlhelp32.h>

// std
#include <functional>
#include <string>
#include <vector>

/*
    TODO:
         - remove std from uintptr_t and size_t and ptrdiff_t
         - IScript base class with pure virtual func Run with ScriptAntiFlashbang and a ManagerScripts
*/
