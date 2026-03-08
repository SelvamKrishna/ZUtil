#pragma once

/// @brief Platform detection
#if defined(_WIN32) || defined(__CYGWIN__)
    #define ZUTIL_PLATFORM_WINDOWS 1
#else
    #define ZUTIL_PLATFORM_WINDOWS 0
#endif

/// @brief Compiler detection
#if defined(__GNUC__) || defined(__clang__)
    #define ZUTIL_COMPILER_GCC_LIKE 1
#else
    #define ZUTIL_COMPILER_GCC_LIKE 0
#endif

/// @brief Symbol visibility
#if ZUTIL_PLATFORM_WINDOWS
    #if defined(ZUTIL_BUILD)
        #define ZUTIL_API __declspec(dllexport)
    #else
        #define ZUTIL_API __declspec(dllimport)
    #endif
#else
    #if ZUTIL_COMPILER_GCC_LIKE
        #define ZUTIL_API __attribute__((visibility("default")))
    #else
        #define ZUTIL_API
    #endif
#endif
