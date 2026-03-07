#pragma once

#include "_export.hpp"
#include "_pro_string.hpp"
#include "zmacros.hpp"

#include <source_location>

namespace zutil
{
    ZUTIL_API void _Assert(bool condition, ProString description, const std::source_location& sourceLocation) noexcept;

    // --- Checks condition if failed aborts process ---
    template <bool Always = {false}>
    inline void Assert(
        bool condition,
        ProString description,
        const std::source_location& sourceLocation = std::source_location::current()
    )
    {
        if constexpr (Always || BUILD_DEBUG) ::zutil::_Assert(condition, description, sourceLocation);
    }

} // namespace zutil
