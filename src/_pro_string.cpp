#include "_pro_string.hpp"

namespace zutil {

ProString::ProString(std::string_view str, ANSI ansi) noexcept : _ansi {ansi}, _str {str} {}

ProString::ProString(const char* str, zutil::ANSI ansi) noexcept : _ansi {ansi} , _str {str} {}

ProString::ProString(const std::source_location& loc) noexcept
    : _ansi { ANSI::EX_Black }
    , _str  { std::format("{}:{} ({})", loc.file_name(), loc.line(), loc.function_name()) }
{}

void ProString::clear() noexcept
{
    this->_str.clear();
}

[[nodiscard]]
ANSI ProString::getColor() const noexcept
{
    return this->_ansi;
}

void ProString::setColor(ANSI ansi_code) noexcept
{
    this->_ansi = ansi_code;
}

[[nodiscard]]
const std::string& ProString::getString() const noexcept
{
    return this->_str;
}

void ProString::setString(std::string_view text) noexcept
{
    this->_str = text;
}

std::ostream& operator<<(std::ostream& os, const ProString& color_str) noexcept
{
    return os << color_str._ansi << color_str._str << ANSI::Reset;
}

[[nodiscard]]
std::string ProString::getParsedString() const noexcept
{
    return (DISABLE_ANSI)
        ? this->_str
        : std::format("{}{}{}", this->_ansi, this->_str, ANSI::Reset);
}


} // namespace zutil
