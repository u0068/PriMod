#pragma once
#include <cstdint>
#include "external/minhook/include/MinHook.h"

// TODO: Include all the structs
struct body;

namespace api
{
    constexpr uintptr_t BASE = reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr));

    template<typename T>
    constexpr T RVA(const uintptr_t rva)
    {
        return reinterpret_cast<T>(BASE + rva);
    }

    template<typename T>
    bool Hook(T& original, T hook)
    {
        void* target = reinterpret_cast<void*>(original);

        auto status = MH_CreateHook(
            target,
            reinterpret_cast<void*>(hook),
            reinterpret_cast<void**>(&original));

        if (status != MH_OK)
        {
            printf("MH_CreateHook failed: %d\n", status);
            return false;
        }

        status = MH_EnableHook(target);

        if (status != MH_OK)
        {
            printf("MH_EnableHook failed: %d\n", status);
            return false;
        }

        return true;
    }

    #include "function_exports.h"
}
