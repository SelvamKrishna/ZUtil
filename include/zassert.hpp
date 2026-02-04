#pragma once

#include "zconfig.hpp"
#include "zansi.hpp"

#include <format>
#include <iostream>
#include <source_location>

namespace zutil {

#ifdef Z_DISABLE_TESTING
inline constexpr bool DISABLE_TESTING {true};
#else
inline constexpr bool DISABLE_TESTING {false};
#endif

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

template <bool Always = false, typename... Args>
inline void assertCnd(
    bool condition,
    const std::format_string<Args...> f_str,
    Args&&... args,
    const std::source_location& loc = std::source_location::current()
) noexcept {
    if constexpr (CURRENT_BUILD == BuildMode::Release && !Always) return;
	if (condition) return;

    const std::string PREFIX = std::format(
        "\n{} {}",
        ColorString{ANSI::BG_Red, "[ASSERT FAILED]"},
        ColorString{ANSI::EX_Black, "{}:{} ({})", loc.file_name(), loc.line(), loc.function_name()}
    );

    std::cerr << PREFIX << " : " << std::format(f_str, std::forward<Args>(args)...) << std::endl;
    std::abort();
}

} // namespace zutil

#ifndef Z_CND_SPLAT

#define Z_CND_SPLAT(cnd) (cnd), "{}", #cnd

#endif
