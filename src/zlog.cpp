#include "_pro_string.hpp"
#include "zlog.hpp"

namespace zutil {

std::ostream& operator<<(std::ostream& outStream, const LogLevel& logLevel) noexcept
{
    static const ProString TRACE_TAGS[4] {
        { ANSI::Blue   , "[DBUG]" },
        { ANSI::Green  , "[INFO]" },
        { ANSI::Yellow , "[WARN]" },
        { ANSI::Red    , "[ERRO]" },
    };

    return outStream << TRACE_TAGS[static_cast<size_t>(logLevel)] << " : ";
}

void _Log(LogLevel logLevel, ProString message) noexcept
{
    std::cout << '\n' << logLevel << message;
}

Logger::Logger(ProString logContext)
    : _logContext(logContext.GetParsedString())
{}

Logger::Logger(std::vector<zutil::ProString> logContextCollection)
{
    std::string combinedContext;

    for (const zutil::ProString& CONTEXT_PORTION : logContextCollection)
        combinedContext += CONTEXT_PORTION.GetParsedString();

    this->_logContext = combinedContext;
}

void Logger::Log(LogLevel logLevel, ProString message) noexcept
{
    this->_LogContext();
    ::zutil::Log(logLevel, message);
}

void Logger::AddContext(const std::string_view context) noexcept
{
    this->_logContext += std::string(context);
}

[[nodiscard]]
const std::string& Logger::GetContext() const noexcept
{
    return this->_logContext;
}

Operation::Operation(
    ProString operationDescription,
    bool isVerbose,
    const std::source_location& sourceLocation
) noexcept
    : _OPERATION_DESCRIPTION  { operationDescription.GetParsedString() }
    , _VERBOSE                { isVerbose }
    , _SOURCE_LOCATION_STRING { ProString{sourceLocation}.GetParsedString() }
{
    if (!_VERBOSE) return;
    ::zutil::Log(LogLevel::DBG, {"Starting : {}", _OPERATION_DESCRIPTION});
}

Operation::~Operation() noexcept
{
    if (!_VERBOSE) return;
    ::zutil::Log(LogLevel::DBG, {"Finished : {}", _OPERATION_DESCRIPTION});
}

void Operation::_LogFailure(ProString message, LogLevel level) const noexcept
{
    ::zutil::Log(level, ProString{"{} {} : {}", _SOURCE_LOCATION_STRING, _OPERATION_DESCRIPTION, message});
}

[[noreturn]]
void Operation::FailAbort(ProString message) const noexcept
{
    this->_LogFailure(message, LogLevel::ERR);
    std::abort();
}

[[noreturn]]
void Operation::FailThrow(std::exception error) const noexcept(false)
{
    throw error;
}

void Operation::FailWarn(ProString message) const noexcept
{
    this->_LogFailure(message, LogLevel::WARN);
}

} // namespace zutil
