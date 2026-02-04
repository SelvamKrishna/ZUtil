#include "zansi.hpp"

namespace zutil {

std::ostream& operator<<(std::ostream& os, const ANSI& ansi) noexcept
{
    return os << "\033[" << static_cast<int>(ansi) << "m";
}

ColorString::ColorString(std::string_view str, ANSI ansi) noexcept : _ansi {ansi}, _str {str} {}

void ColorString::clear() noexcept
{
    this->_str.clear();
}

[[nodiscard]]
ANSI ColorString::getColor() const noexcept
{
    return this->_ansi;
}

void ColorString::setColor(ANSI ansi_code) noexcept
{
    this->_ansi = ansi_code;
}

[[nodiscard]]
const std::string& ColorString::getString() const noexcept
{
    return this->_str;
}

void ColorString::setString(std::string_view text) noexcept
{
    this->_str = text;
}

std::ostream& operator<<(std::ostream& os, const ColorString& color_str) noexcept
{
    return os << color_str._ansi << color_str._str << ANSI::Reset;
}

} // namespace zutil
