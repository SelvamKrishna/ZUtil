#pragma once

#include <cstdint>
#include <format>
#include <ostream>
#include <string>

namespace zutil {

/**
 * @enum ANSI
 * @brief ANSI escape codes for terminal text styling and colors.
 *
 * This enumeration defines a subset of commonly supported ANSI
 * escape codes for modifying terminal output appearance.
 *
 * @note These values assume an ANSI-compatible terminal.
 * @note Behavior is undefined on terminals that do not support ANSI codes.
 */
enum class ANSI : uint8_t {
/** Text Attributes VVV */
    Reset          = 0,
    Bold           = 1,
    Dim            = 2,
    Italic         = 3,
    Underline      = 4,
    Blink          = 5,
    Inverse        = 7,
    Hidden         = 8,
    Strikethrough  = 9,
/** Regular Colors VVV */
    Black          = 30,
    Red            = 31,
    Green          = 32,
    Yellow         = 33,
    Blue           = 34,
    Magenta        = 35,
    Cyan           = 36,
    White          = 37,
/** Background Colors VVV */
    BG_Black       = 40,
    BG_Red         = 41,
    BG_Green       = 42,
    BG_Yellow      = 43,
    BG_Blue        = 44,
    BG_Magenta     = 45,
    BG_Cyan        = 46,
    BG_White       = 47,
/** Bright Colors VVV */
    EX_Black       = 90,
    EX_Red         = 91,
    EX_Green       = 92,
    EX_Yellow      = 93,
    EX_Blue        = 94,
    EX_Magenta     = 95,
    EX_Cyan        = 96,
    EX_White       = 97,
/** Bright Background Colors VVV */
    BG_EX_Black    = 100,
    BG_EX_Red      = 101,
    BG_EX_Green    = 102,
    BG_EX_Yellow   = 103,
    BG_EX_Blue     = 104,
    BG_EX_Magenta  = 105,
    BG_EX_Cyan     = 106,
    BG_EX_White    = 107,
};

/**
 * @brief Streams an ANSI escape sequence to an output stream.
 *
 * This operator emits the ANSI escape code corresponding
 * to the given `ANSI` value.
 *
 * @param os   Output stream
 * @param ansi ANSI code to emit
 * @return Reference to the output stream
 */
std::ostream& operator<<(std::ostream& os, const ANSI& ansi) noexcept;

/**
 * @class ColorString
 * @brief String wrapper with optional ANSI color formatting.
 *
 * `ColorString` associates a text string with an ANSI color code
 * and emits the appropriate escape sequences when streamed.
 */
class ColorString final {
private:
    ANSI        _ansi { ANSI::Reset };
    std::string _str;

public:
    /**
     * @brief Constructs an empty color string.
     */
    ColorString() noexcept = default;

    /**
     * @brief Constructs a color string from a string view.
     *
     * @param str  Text content
     * @param ansi ANSI color code (defaults to Reset)
     */
    ColorString(std::string_view str, ANSI ansi = ANSI::Reset) noexcept;

    /**
     * @brief Constructs a formatted color string.
     *
     * Formats the given arguments using `std::format` and stores
     * the resulting string.
     *
     * @tparam Args Format argument types
     * @param f_str Format string
     * @param arg   Format arguments
     */
    template <typename... Args>
    ColorString(const std::format_string<Args...> f_str, Args&&... arg)
        : _str { std::format(f_str, std::forward<Args>(arg)...) }
    {}

    /**
     * @brief Constructs a formatted color string with an ANSI color.
     *
     * @tparam Args Format argument types
     * @param ansi  ANSI color code
     * @param f_str Format string
     * @param arg   Format arguments
     */
    template <typename... Args>
    ColorString(ANSI ansi, const std::format_string<Args...> f_str, Args&&... arg)
        : _ansi { ansi }
        , _str  { std::format(f_str, std::forward<Args>(arg)...) }
    {}

    ~ColorString() noexcept = default;

    ColorString(ColorString&&)                 noexcept = default;
    ColorString(const ColorString&)            noexcept = default;
    ColorString& operator=(ColorString&&)      noexcept = default;
    ColorString& operator=(const ColorString&) noexcept = default;

    /**
     * @brief Clears the stored string content.
     */
    void clear() noexcept;

    /**
     * @brief Returns the currently associated ANSI color.
     *
     * @return ANSI color code
     */
    [[nodiscard]]
    ANSI getColor() const noexcept;

    /**
     * @brief Sets the ANSI color code.
     *
     * @param ansi_code New ANSI color
     */
    void setColor(ANSI ansi_code) noexcept;

    /**
     * @brief Streams the colored string to an output stream.
     *
     * Emits the ANSI escape sequence, followed by the string
     * content, and finally resets the formatting.
     *
     * @param os        Output stream
     * @param color_str Color string to emit
     * @return Reference to the output stream
     */
    friend std::ostream& operator<<(std::ostream& os, const ColorString& color_str) noexcept;
};

} // namespace zutil
