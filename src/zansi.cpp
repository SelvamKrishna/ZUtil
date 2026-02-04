#include "zansi.hpp"

namespace zutil {

std::ostream& operator<<(std::ostream& os, const ANSI& ansi) noexcept
{
    return os << "\033[" << static_cast<int>(ansi) << "m";
}

ANSIString::ANSIString(std::string_view str, ANSI ansi) noexcept : _ansi {ansi}, _str {str} {}

void ANSIString::clear() noexcept
{
    this->_str.clear();
}

[[nodiscard]]
ANSI ANSIString::getColor() const noexcept
{
    return this->_ansi;
}

void ANSIString::setColor(ANSI ansi_code) noexcept
{
    this->_ansi = ansi_code;
}

[[nodiscard]]
const std::string& ANSIString::getString() const noexcept
{
    return this->_str;
}

void ANSIString::setString(std::string_view text) noexcept
{
    this->_str = text;
}

std::ostream& operator<<(std::ostream& os, const ANSIString& color_str) noexcept
{
    return os << color_str._ansi << color_str._str << ANSI::Reset;
}

[[nodiscard]]
std::string ANSIString::getParsedString() const noexcept
{
    return (DISABLE_ANSI)
        ? this->_str
        : std::format("{}{}{}", this->_ansi, this->_str, ANSI::Reset);
}

} // namespace zutil
