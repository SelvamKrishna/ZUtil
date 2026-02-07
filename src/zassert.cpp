#include "zassert.hpp"

#include <iostream>

namespace zutil {

inline void _assertCnd(
    bool condition,
    ProString description,
    const std::source_location& loc
) noexcept
{
	if (condition) return;

    std::cerr
        << '\n'
        << ProString{"[ASSERT]", ANSI::BG_Red}
        << ProString{loc}
        << " : "
        << description
        << std::endl
    ;

    std::abort();
}

} // namespace zutil
