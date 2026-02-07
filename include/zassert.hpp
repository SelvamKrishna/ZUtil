#pragma once

#include "_pro_string.hpp"

#include <source_location>

namespace zutil {

#ifdef NDEBUG
inline constexpr bool RELEASE_BUILD {true};
#else
inline constexpr bool RELEASE_BUILD {false};
#endif

void _assertCnd(bool condition, ProString description, const std::source_location& loc) noexcept;

template <bool Always = {false}>
inline void assertCnd(
    bool condition,
    ProString description,
    const std::source_location& loc = std::source_location::current()
)
{
    if constexpr (Always || !RELEASE_BUILD)
        _assertCnd(condition, description, loc);
}

} // namespace zutil

#ifndef Z_CND_SPLAT

#define Z_CND_SPLAT(cnd) (cnd), {"{}", #cnd}

#endif
