#include "log.hpp"
#include "ansi.hpp"

namespace zutil {

std::ostream& operator<<(std::ostream& os, const LogLevel& log_lvl) noexcept
{
    static const ColorString TAGS[4] {
        { ANSI::Blue   , "[DBUG]" },
        { ANSI::Green  , "[INFO]" },
        { ANSI::Yellow , "[WARN]" },
        { ANSI::Red    , "[ERRO]" },
    };

    return os << TAGS[static_cast<size_t>(log_lvl)] << " : ";
}

Logger::Logger(const std::string_view log_prefix)
    : _log_prefix(std::string(log_prefix))
{}

Logger::Logger(std::vector<std::string> log_parts)
{
    std::string prefix;

    for (const std::string& PART : log_parts)
        prefix += PART;

    this->_log_prefix = prefix;
}

} // namespace zutil
