#pragma once

#include "_export.hpp"
#include "_pro_string.hpp"

#include <source_location>

namespace zutil
{

#ifdef NDEBUG
    inline constexpr bool RELEASE_BUILD {true};
#else
    inline constexpr bool RELEASE_BUILD {false};
#endif

    ZUTIL_API void _Assert(bool condition, ProString description, const std::source_location& sourceLocation) noexcept;

    template <bool Always = {false}>
    inline void Assert(
        bool condition,
        ProString description,
        const std::source_location& sourceLocation = std::source_location::current()
    )
    {
        if constexpr (Always || !RELEASE_BUILD)
            ::zutil::_Assert(condition, description, sourceLocation);
    }

} // namespace zutil
