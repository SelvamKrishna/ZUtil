#include "_pro_string.hpp"

namespace zutil {

ProString::ProString(std::string_view string, ANSI ansiCode) noexcept
    : _ansiCode {ansiCode}
    , _string   {string}
{}

ProString::ProString(const char* string, zutil::ANSI ansiCode) noexcept
    : _ansiCode {ansiCode}
    , _string   {string}
{}

ProString::ProString(const std::source_location& sourceLocation, bool isVerbose) noexcept
    : _ansiCode { ANSI::EX_Black }
{
    this->_string = (isVerbose)
        ? std::format(
            "[{} ({}:{})]",
            sourceLocation.function_name(),
            sourceLocation.file_name(),
            sourceLocation.line()
        )
        : std::format(
            "[{}:{}]",
            sourceLocation.file_name(),
            sourceLocation.line()
        )
    ;
}

void ProString::Clear() noexcept
{
    this->_string.clear();
}

[[nodiscard]]
ANSI ProString::GetColor() const noexcept
{
    return this->_ansiCode;
}

void ProString::SetColor(ANSI ansiCode) noexcept
{
    this->_ansiCode = ansiCode;
}

[[nodiscard]]
const std::string& ProString::GetString() const noexcept
{
    return this->_string;
}

void ProString::SetString(std::string_view string) noexcept
{
    this->_string = string;
}

std::ostream& operator<<(std::ostream& outStream, const ProString& proString) noexcept
{
    return outStream << proString.GetColor() << proString.GetString() << ANSI::Reset;
}

[[nodiscard]]
std::string ProString::GetParsedString() const noexcept
{
    return (DISABLE_ANSI)
        ? this->GetString()
        : std::format("{}{}{}", this->GetColor(), this->GetString(), ANSI::Reset);
}

} // namespace zutil
