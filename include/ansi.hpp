#pragma once

#include <cstdint>
#include <format>
#include <ostream>
#include <string>

namespace zutil {

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

std::ostream& operator<<(std::ostream& os, const ANSI& ansi) noexcept;

class ColorString final {
private:
    ANSI _ansi { ANSI::Reset };
    std::string _str;

public:
    ColorString() noexcept = default;

    ColorString(std::string_view str, ANSI ansi = ANSI::Reset) noexcept;

    template <typename... Args>
    ColorString(const std::format_string<Args...> f_str, Args&&... arg)
        : _str { std::format(f_str, std::forward<Args>(arg)...) }
    {}

    template <typename... Args>
    ColorString(ANSI ansi, const std::format_string<Args...> f_str, Args&&... arg)
        : _ansi { ansi }
        , _str { std::format(f_str, std::forward<Args>(arg)...) }
    {}

    ~ColorString() noexcept = default;

    constexpr ColorString(ColorString&&)                 noexcept = default;
    constexpr ColorString(const ColorString&)            noexcept = default;
    constexpr ColorString& operator=(ColorString&&)      noexcept = default;
    constexpr ColorString& operator=(const ColorString&) noexcept = default;

    void clear() noexcept;

    [[nodiscard]]
    ANSI getColor() const noexcept;

    void setColor(ANSI ansi_code) noexcept;

    friend std::ostream& operator<<(std::ostream& os, const ColorString& color_str) noexcept;
};

} // namespace zutil
