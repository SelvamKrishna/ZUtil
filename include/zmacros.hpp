#pragma once

namespace zutil
{
#ifdef NDEBUG
    inline constexpr bool BUILD_DEBUG = false;
#else
    inline constexpr bool BUILD_DEBUG = true;
#endif
} // namespace zutil

// Logging Macros:

#define Z_VAR_SPLAT(variable) \
    {"{} = ({})", ::zutil::ProString{::zutil::ANSI::Magenta, #variable}, (variable)}

#define Z_CND_SPLAT(condition) \
    (condition), {"{}", #condition}

// Build Mode Macros:

#define Z_ON_DBG \
    if constexpr (::zutil::BUILD_DEBUG)

#define Z_ON_RLS \
    if constexpr (!::zutil::BUILD_DEBUG)
