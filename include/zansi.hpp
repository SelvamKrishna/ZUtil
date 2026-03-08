#pragma once

#include <cstdint>
#include <format>
#include <ostream>

namespace zutil
{

#ifdef Z_DISABLE_ANSI
    inline constexpr bool DISABLE_ANSI {true};
#else
    inline constexpr bool DISABLE_ANSI {false};
#endif

    /// ---
    /// @brief ANSI escape codes for terminal text formatting.
    /// Provides foreground, background, extended colors, and text style flags.
    /// Can be used with both `std::ostream` and `std::format`.
    /// ---
    enum class ANSI : uint8_t
    {
        Reset          = 0,   ///< Reset all styles
        Bold           = 1,   ///< Bold text
        Dim            = 2,   ///< Dim text
        Italic         = 3,   ///< Italic text
        Underline      = 4,   ///< Underlined text
        Blink          = 5,   ///< Blinking text
        Inverse        = 7,   ///< Inverse colors
        Hidden         = 8,   ///< Hidden text
        Strikethrough  = 9,   ///< Strikethrough text

        Black          = 30,  ///< Foreground Black
        Red            = 31,  ///< Foreground Red
        Green          = 32,  ///< Foreground Green
        Yellow         = 33,  ///< Foreground Yellow
        Blue           = 34,  ///< Foreground Blue
        Magenta        = 35,  ///< Foreground Magenta
        Cyan           = 36,  ///< Foreground Cyan
        White          = 37,  ///< Foreground White

        BG_Black       = 40,  ///< Background Black
        BG_Red         = 41,  ///< Background Red
        BG_Green       = 42,  ///< Background Green
        BG_Yellow      = 43,  ///< Background Yellow
        BG_Blue        = 44,  ///< Background Blue
        BG_Magenta     = 45,  ///< Background Magenta
        BG_Cyan        = 46,  ///< Background Cyan
        BG_White       = 47,  ///< Background White

        EX_Black       = 90,  ///< Extended Foreground Black
        EX_Red         = 91,  ///< Extended Foreground Red
        EX_Green       = 92,  ///< Extended Foreground Green
        EX_Yellow      = 93,  ///< Extended Foreground Yellow
        EX_Blue        = 94,  ///< Extended Foreground Blue
        EX_Magenta     = 95,  ///< Extended Foreground Magenta
        EX_Cyan        = 96,  ///< Extended Foreground Cyan
        EX_White       = 97,  ///< Extended Foreground White

        BG_EX_Black    = 100, ///< Extended Background Black
        BG_EX_Red      = 101, ///< Extended Background Red
        BG_EX_Green    = 102, ///< Extended Background Green
        BG_EX_Yellow   = 103, ///< Extended Background Yellow
        BG_EX_Blue     = 104, ///< Extended Background Blue
        BG_EX_Magenta  = 105, ///< Extended Background Magenta
        BG_EX_Cyan     = 106, ///< Extended Background Cyan
        BG_EX_White    = 107, ///< Extended Background White
    };

    /// @brief Stream insertion operator for ANSI codes.
    /// Outputs the ANSI escape sequence to the given stream unless
    /// `DISABLE_ANSI` is true, in which case no output is produced.
    /// @param outStream Output stream.
    /// @param ansiCode ANSI code to insert.
    /// @return Reference to the output stream.
    inline std::ostream& operator<<(std::ostream& outStream, const ANSI& ansiCode) noexcept
    {
        return (DISABLE_ANSI) ? outStream : outStream << "\033[" << static_cast<int>(ansiCode) << "m";
    }

} // namespace zutil

/// @brief Formatter specialization for `zutil::ANSI` to support `std::format`.
template <>
struct std::formatter<zutil::ANSI>
{
    constexpr auto parse(std::format_parse_context &ctx) -> std::format_parse_context::const_iterator { return ctx.begin(); }

    auto format(const zutil::ANSI &ansiCode, std::format_context &ctx) const
    {
        return (zutil::DISABLE_ANSI)
            ? std::format_to(ctx.out(), "")
            : std::format_to(ctx.out(), "\033[{}m", static_cast<int>(ansiCode));
    }
};
