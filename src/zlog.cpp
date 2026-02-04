#include "zansi.hpp"
#include "zlog.hpp"

namespace zutil {

std::ostream& operator<<(std::ostream& os, const LogLevel& log_lvl) noexcept
{
    static const ANSIString TAGS[4] {
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

Logger::Logger(std::vector<zutil::ANSIString> log_parts)
{
    std::string prefix;

    for (const zutil::ANSIString& PART : log_parts)
        prefix += PART.getParsedString();

    this->_log_prefix = prefix;
}

void Logger::addPrefix(const std::string_view prefix) noexcept
{
    this->_log_prefix += std::string(prefix);
}

[[nodiscard]]
const std::string& Logger::getPrefix() const noexcept
{
    return this->_log_prefix;
}

} // namespace zutil
