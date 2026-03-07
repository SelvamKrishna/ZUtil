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

// --- Can be used within zutil::Test, zutil::Assert to print the condition as string ---
#define Z_VAR_SPLAT(variable) \
    {"{} = ({})", ::zutil::ProString{::zutil::ANSI::Magenta, #variable}, (variable)}

// --- Can be used within zutil::Test, zutil::Assert to print the condition as string ---
#define Z_CND_SPLAT(condition) \
    (condition), {"{}", #condition}

// Build Mode Macros:

// --- Compile time check of Build type ---
#define Z_ON_DBG \
    if constexpr (::zutil::BUILD_DEBUG)

// --- Compile time check of Build type ---
#define Z_ON_RLS \
    if constexpr (!::zutil::BUILD_DEBUG)

// Misc Macros:

// --- Used to access a unique bit ---
#define Z_BIT(bitPos) \
    (1 << number)
