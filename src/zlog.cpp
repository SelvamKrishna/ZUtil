#include "_pro_string.hpp"
#include "zlog.hpp"

namespace zutil {

std::ostream& operator<<(std::ostream& os, const LogLevel& log_lvl) noexcept
{
    static const ProString TAGS[4] {
        { ANSI::Blue   , "[DBUG]" },
        { ANSI::Green  , "[INFO]" },
        { ANSI::Yellow , "[WARN]" },
        { ANSI::Red    , "[ERRO]" },
    };

    return os << TAGS[static_cast<size_t>(log_lvl)] << " : ";
}

void _log(LogLevel level, ProString message) noexcept
{
    if (!DISABLE_LOGGING) std::cout << '\n' << level << message;
}

Logger::Logger(ProString log_prefix)
    : _log_prefix(log_prefix.getParsedString())
{}

Logger::Logger(std::vector<zutil::ProString> log_parts)
{
    std::string prefix;

    for (const zutil::ProString& PART : log_parts)
        prefix += PART.getParsedString();

    this->_log_prefix = prefix;
}

void Logger::log(LogLevel level, ProString message) noexcept
{
    ::zutil::log(level, message);
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


Operation::Operation(ProString op_name, bool trace) noexcept
    : _OP_NAME { op_name.getParsedString() }
    , _TRACE   { trace }
{
    if (!_TRACE) return;
    ::zutil::log(LogLevel::DBG, {"Starting : {}", _OP_NAME});
}

Operation::~Operation() noexcept
{
    if (!_TRACE) return;
    ::zutil::log(LogLevel::DBG, {"Finished : {}", _OP_NAME});
}

} // namespace zutil
