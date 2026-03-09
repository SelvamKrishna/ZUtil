#pragma once

/// @brief Platform detection
#if defined(_WIN32) || defined(__CYGWIN__)
    #define ZEN_PLATFORM_WINDOWS 1
#else
    #define ZEN_PLATFORM_WINDOWS 0
#endif

/// @brief Compiler detection
#if defined(__GNUC__) || defined(__clang__)
    #define ZEN_COMPILER_GCC_LIKE 1
#else
    #define ZEN_COMPILER_GCC_LIKE 0
#endif

/// @brief Symbol visibility
#if ZEN_PLATFORM_WINDOWS
    #if defined(ZEN_BUILD)
        #define ZEN_API __declspec(dllexport)
    #else
        #define ZEN_API __declspec(dllimport)
    #endif
#else
    #if ZEN_COMPILER_GCC_LIKE
        #define ZEN_API __attribute__((visibility("default")))
    #else
        #define ZEN_API
    #endif
#endif
