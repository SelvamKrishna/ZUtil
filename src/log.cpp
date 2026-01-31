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
    os << log_str.str();
    return os;
}

void Log::_writeTimestamp() noexcept
{
    std::cout << "[HH:MM:SS::DD:MM:YYYY]";
}

void Log::_writeMsg(std::string_view prefix, const LogString& log_str) noexcept
{
    if (false)
    {
        Log::_writeTimestamp();
    }

    std::cout << prefix << " : " << log_str << "\n";
}

void Log::debugMsg(const LogString& log_str) noexcept
{
    Log::_writeMsg("[DBUG]", log_str);
}

void Log::infoMsg(const LogString& log_str) noexcept
{
    Log::_writeMsg("[INFO]", log_str);
}

void Log::warnMsg(const LogString& log_str) noexcept
{
    Log::_writeMsg("[WARN]", log_str);
}

void Log::errorMsg(const LogString& log_str) noexcept
{
    Log::_writeMsg("[ERRO]", log_str);
}

} // namespace zutils
