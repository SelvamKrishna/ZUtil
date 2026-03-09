#ifndef ZEN_BUILD
#define ZEN_BUILD
#endif

#include "z_assert.hpp"

#include <iostream>

namespace zen
{

    void _Assert(bool condition, ProString description, const std::source_location& sourceLocation)
    {
        if (condition) return;

        std::cerr
            << std::format(
                "{}{} : {}",
                ProString{"\n[ASSERT]", ANSI::BG_Red},
                ProString{sourceLocation, true},
                (description.GetString().empty() ? ProString{"No description provided."} : description)
            )
            << std::endl
        ;

        std::abort();
    }

} // namespace zen
