#pragma once

#include <cstdio>  // IWYU pragma: keep
#include <cstdlib> // IWYU pragma: keep
#include <cstddef> // IWYU pragma: keep
#include <cassert> // IWYU pragma: keep

namespace zen
{

#ifdef NDEBUG
    inline constexpr bool BUILD_DEBUG = false;
#else
    inline constexpr bool BUILD_DEBUG = true;
#endif

} // namespace zen

// ============================================================
// Logging / Debug Helpers
// ============================================================

/// @brief Expands a variable to `"name = (value)"`.
#define Z_VAR_SPLAT(variable) \
    {"{} = ({})", ::zen::ProString{::zen::ANSI::Magenta, #variable}, (variable)}

/// @brief Expands a condition and its textual representation.
#define Z_CND_SPLAT(condition) \
    (condition), {"{}", #condition}

// ============================================================
// Build Mode Macros
// ============================================================

/// @brief Execute code only in debug builds.
#define Z_ON_DBG \
    if constexpr (::zen::BUILD_DEBUG)

/// @brief Execute code only in release builds.
#define Z_ON_RLS \
    if constexpr (!::zen::BUILD_DEBUG)

// ============================================================
// Compiler Hints
// ============================================================

#if defined(__clang__) || defined(__GNUC__)
#define Z_LIKELY(x) \
    __builtin_expect(!!(x), 1)
#define Z_UNLIKELY(x) \
    __builtin_expect(!!(x), 0)
#else
#define Z_LIKELY(x) \
    (x)
#define Z_UNLIKELY(x) \
    (x)
#endif

#if defined(_MSC_VER)
#define Z_FORCE_INLINE __forceinline
#define Z_NO_INLINE __declspec(noinline)
#else
#define Z_FORCE_INLINE inline __attribute__((always_inline))
#define Z_NO_INLINE __attribute__((noinline))
#endif

/// @brief Marks code as unreachable.
#if defined(__clang__) || defined(__GNUC__)
#define Z_UNREACHABLE() \
    __builtin_unreachable()
#elif defined(_MSC_VER)
#define Z_UNREACHABLE() \
    __assume(false)
#else
#define Z_UNREACHABLE() \
    std::abort()
#endif

/// @brief Compile-time TODO reminder.
#if defined(_MSC_VER)
#define Z_TODO(warningMessage) \
    __pragma(message(__FILE__ "(" Z_STRINGIFY(__LINE__) "): TODO: " warningMessage))
#else
#define Z_TODO(warningMessage) \
    _Pragma(Z_STRINGIFY(message("TODO: " warningMessage)))
#endif

// ============================================================
// Token / String Utilities
// ============================================================

/// @brief Converts a token to a string.
#define Z_STRINGIFY(x) \
    #x

/// @brief Expands then stringifies a token.
#define Z_EXPAND_AND_STRINGIFY(x) \
    Z_STRINGIFY(x)

/// @brief Token concatenation.
#define Z_CONCAT(a, b) \
    a##b

/// @brief Expands then concatenates tokens.
#define Z_CONCAT_EXPAND(a, b) \
    Z_CONCAT(a, b)

/// @brief Generates a unique identifier using line number.
#define Z_UNIQUE_NAME(base) \
    Z_CONCAT_EXPAND(base, __LINE__)

// ============================================================
// Bit / Memory Utilities
// ============================================================

/// @brief Creates a bit mask at the given position.
#define Z_BIT(bitPos) \
    (1u << (bitPos))

// ============================================================
// Assertion
// ============================================================

#if defined (NDEBUG)

#define Z_ASSERT(expression, description) \
    ((void)0)

#else

#define Z_ASSERT(expression) do {                                       \
    if ((expression)) break;                                            \
    std::fprintf(                                                       \
        stderr,                                                         \
        "ZEN_ASSERT FAILED\n  Condition: %s\n  File: %s\n  Line: %d\n", \
        #expression, __FILE__, __LINE__                                 \
    );                                                                  \
    std::abort();                                                       \
} while (0)

#endif
