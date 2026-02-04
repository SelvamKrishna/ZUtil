#pragma once

#include "zansi.hpp"

#include <format>
#include <iostream>

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
        << ANSIString{ANSI::Blue, "[TEST]"}
        << ((condition) ? ANSIString{ANSI::Green, "[PASS]"} : ANSIString{ANSI::Red, "[FAIL]"})
        << " : "
        << std::format(f_str, std::forward<Args>(args)...)
    ;
}

} // namespace zutil
