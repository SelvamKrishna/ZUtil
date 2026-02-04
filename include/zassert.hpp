#pragma once

#include "zconfig.hpp"
#include "zansi.hpp"

#include <format>
#include <iostream>
#include <source_location>

namespace zutil {

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
        ANSIString{ANSI::BG_Red, "[ASSERT FAILED]"},
        ANSIString{ANSI::EX_Black, "{}:{} ({})", loc.file_name(), loc.line(), loc.function_name()}
    );

    std::cerr << PREFIX << " : " << std::format(f_str, std::forward<Args>(args)...) << std::endl;
    std::abort();
}

} // namespace zutil

#ifndef Z_CND_SPLAT

#define Z_CND_SPLAT(cnd) (cnd), "{}", #cnd

#endif
