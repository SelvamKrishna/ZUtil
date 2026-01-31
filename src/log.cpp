#include "log.hpp"

namespace zutils {

LogString::LogString(const char* str) noexcept : _str { str } {}

void LogString::clear() noexcept
{
    this->_str.clear();
}

inline const std::string& LogString::str() const noexcept
{
    return this->_str;
}

std::ostream& operator<<(std::ostream& os, const LogString& log_str) noexcept
{
    return os << log_str.str();
}

ColorString::ColorString(const char* str) noexcept : LogString {str} {}

ColorString::ColorString(ANSI ansi, const char* str) noexcept : LogString {str}, _ansi {ansi} {}

[[nodiscard]]
ANSI ColorString::getColor() const noexcept
{
    return this->_ansi;
}

void ColorString::setColor(ANSI ansi_code) noexcept
{
    this->_ansi = ansi_code;
}

std::ostream& operator<<(std::ostream& os, const ColorString& log_str) noexcept
{
    return os << log_str._ansi << log_str._str << ANSI::Reset;
}

std::ostream& operator<<(std::ostream& os, const LogLevel& log_lvl) noexcept
{
    static const ColorString TAGS[4] {
        ColorString { ANSI::Blue   , "[DBUG]" },
        ColorString { ANSI::Green  , "[INFO]" },
        ColorString { ANSI::Yellow , "[WARN]" },
        ColorString { ANSI::Red    , "[ERRO]" },
    };

    return os << TAGS[static_cast<size_t>(log_lvl)];
}

void Log::_writeMsg(LogLevel log_lvl, const LogString& log_str) noexcept
{
    std::cout << log_lvl << " : " << log_str << "\n";
}

void Log::debugMsg(const LogString& log_str) noexcept
{
    Log::_writeMsg(LogLevel::Debug, log_str);
}

void Log::infoMsg(const LogString& log_str) noexcept
{
    Log::_writeMsg(LogLevel::Info, log_str);
}

void Log::warnMsg(const LogString& log_str) noexcept
{
    Log::_writeMsg(LogLevel::Warn, log_str);
}

void Log::errorMsg(const LogString& log_str) noexcept
{
    Log::_writeMsg(LogLevel::Error, log_str);
}

} // namespace zutils
