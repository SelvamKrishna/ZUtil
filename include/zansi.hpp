#pragma once

#include <cstdint>
#include <format>
#include <ostream>
#include <string>

namespace zutil {

#ifdef Z_DISABLE_ANSI
inline constexpr bool DISABLE_ANSI {true};
#else
inline constexpr bool DISABLE_ANSI {false};
#endif

enum class ANSI : uint8_t {
    Reset          = 0,
    Bold           = 1,
    Dim            = 2,
    Italic         = 3,
    Underline      = 4,
    Blink          = 5,
    Inverse        = 7,
    Hidden         = 8,
    Strikethrough  = 9,

    Black          = 30,
    Red            = 31,
    Green          = 32,
    Yellow         = 33,
    Blue           = 34,
    Magenta        = 35,
    Cyan           = 36,
    White          = 37,

    BG_Black       = 40,
    BG_Red         = 41,
    BG_Green       = 42,
    BG_Yellow      = 43,
    BG_Blue        = 44,
    BG_Magenta     = 45,
    BG_Cyan        = 46,
    BG_White       = 47,

    EX_Black       = 90,
    EX_Red         = 91,
    EX_Green       = 92,
    EX_Yellow      = 93,
    EX_Blue        = 94,
    EX_Magenta     = 95,
    EX_Cyan        = 96,
    EX_White       = 97,

    BG_EX_Black    = 100,
    BG_EX_Red      = 101,
    BG_EX_Green    = 102,
    BG_EX_Yellow   = 103,
    BG_EX_Blue     = 104,
    BG_EX_Magenta  = 105,
    BG_EX_Cyan     = 106,
    BG_EX_White    = 107,
};

#ifdef Z_DISABLE_ANSI
inline std::ostream& operator<<(std::ostream& os, const ANSI& ansi) noexcept
{
    (void)ansi;
    return os;
}
#else
std::ostream& operator<<(std::ostream& os, const ANSI& ansi) noexcept;
#endif

class ANSIString final {
private:
    ANSI        _ansi { ANSI::Reset };
    std::string _str;

public:
    ANSIString() noexcept = default;

    ANSIString(std::string_view str, ANSI ansi = ANSI::Reset) noexcept;

    template <typename... Args>
    ANSIString(const std::format_string<Args...> f_str, Args&&... arg)
        : _str { std::format(f_str, std::forward<Args>(arg)...) }
    {}

    template <typename... Args>
    ANSIString(ANSI ansi, const std::format_string<Args...> f_str, Args&&... arg)
        : _ansi { ansi }
        , _str  { std::format(f_str, std::forward<Args>(arg)...) }
    {}

    ~ANSIString() noexcept = default;

    ANSIString(ANSIString&&)                 noexcept = default;
    ANSIString(const ANSIString&)            noexcept = default;
    ANSIString& operator=(ANSIString&&)      noexcept = default;
    ANSIString& operator=(const ANSIString&) noexcept = default;

    void clear() noexcept;

    [[nodiscard]]
    ANSI getColor() const noexcept;

    void setColor(ANSI ansi_code) noexcept;

    [[nodiscard]]
    const std::string& getString() const noexcept;

    void setString(std::string_view text) noexcept;

    [[nodiscard]]
    std::string getParsedString() const noexcept;

    friend std::ostream& operator<<(std::ostream& os, const ANSIString& color_str) noexcept;
};

} // namespace zutil

template <>
struct std::formatter<zutil::ANSI> {
    constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

    auto format(const zutil::ANSI &ansi, std::format_context &ctx) const
    {
        return (zutil::DISABLE_ANSI)
            ? std::format_to(ctx.out(), "")
            : std::format_to(ctx.out(), "\033[{}m", static_cast<int>(ansi));
    }
};

template <>
struct std::formatter<zutil::ANSIString> {
    constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

    auto format(const zutil::ANSIString &ansi_str, std::format_context &ctx) const
    {
        return std::format_to(ctx.out(), "{}", ansi_str.getParsedString());
    }
};
