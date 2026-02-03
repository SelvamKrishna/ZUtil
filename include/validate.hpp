#pragma once

#include "ansi.hpp"

#include <format>
#include <iostream>
#include <source_location>

namespace zutil {

inline constexpr bool DISABLE_TESTING {
    #ifdef Z_DISABLE_TESTING
        true
    #else
        false
    #endif
};

enum class BuildMode {
    Debug,
    Release,
};

template <typename... Args>
inline void testCase(bool condition, const std::format_string<Args...> f_str, Args&&... args) noexcept
{
    if constexpr (DISABLE_TESTING) return;
    std::cout
        << "\n"
        << ColorString{ANSI::Blue, "[TEST]"}
        << ((condition) ? ColorString{ANSI::Green, "[PASS]"} : ColorString{ANSI::Red, "[FAIL]"})
        << " : "
        << std::format(f_str, std::forward<Args>(args)...)
    ;
}

template <BuildMode OnMode = BuildMode::Debug, typename... Args>
inline void assertCnd(bool condition, const std::format_string<Args...> f_str, Args&&... args, const std::source_location& loc = std::source_location::current()) noexcept
{
#ifdef NDEBUG
    if constexpr (OnMode == BuildMode::Debug) return;
#endif

	if (condition) return;

    std::cerr
        << std::format(
            "\n{} {}:{} ({}) : {}",
            ColorString{ANSI::BG_Red, "[ASSERT FAILED]"},
            loc.file_name(),
            loc.line(),
            loc.function_name(),
            std::format(f_str, std::forward<Args>(args)...)
        )
        << std::endl
    ;

    std::abort();
}

} // namespace zutil

#ifndef Z_CND_SPLAT

#define Z_CND_SPLAT(cnd) (cnd), "{}", #cnd

#endif
