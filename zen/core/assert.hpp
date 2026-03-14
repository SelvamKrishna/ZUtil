#pragma once

#include "_export.hpp"
#include "_pro_string.hpp"
#include "macros.hpp"

#include <source_location>

namespace zen::core
{
    /// @brief Internal assert logic implementation
    /// Evaluates a condition and abort's program on failure.
    /// @param condition Result of the assert condition.
    /// @param description Description of the test.
    /// @param sourceLocation file, function, line number for debugging.
    /// @note This function is intended to be called through zen::core::Assert().
    ZEN_API void _Assert(bool condition, ProString description, const std::source_location& sourceLocation);

    /// @brief Evaluates a condition and abort's program on failure.
    /// @tparam Always ensures function operation on all builds.
    /// @param condition Result of the assert condition.
    /// @param description Description of the test.
    /// @param sourceLocation file, function, line number for debugging.
    /// @note This function become's a compile-time no-op on Release Builds, unless `Always` is set to true.
    template <bool Always = {false}>
    inline void Assert(
        bool condition,
        ProString description,
        const std::source_location& sourceLocation = std::source_location::current()
    )
    {
        if constexpr (Always || BUILD_DEBUG) ::zen::core::_Assert(condition, description, sourceLocation);
    }

} // namespace zen::core
