#include "zassert.hpp"

#include <iostream>

namespace zutil {

void _Assert(bool condition, ProString description, const std::source_location& sourceLocation) noexcept
{
	if (condition) return;

    std::cerr
        << ProString{"\n[ASSERT]", ANSI::BG_Red} << ProString{sourceLocation, true}
        << " : " << description << std::endl
    ;

    std::abort();
}

} // namespace zutil
