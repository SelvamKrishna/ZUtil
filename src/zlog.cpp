#include "_pro_string.hpp"
#include "zlog.hpp"

namespace zutil {

std::ostream& operator<<(std::ostream& outStream, const LogLevel& logLevel) noexcept
{
    switch (logLevel)
    {
        case LogLevel::DBG : return outStream << ProString { ANSI::Blue     , "[DBUG]" } << " : " ;
        case LogLevel::INFO: return outStream << ProString { ANSI::Green    , "[INFO]" } << " : " ;
        case LogLevel::WARN: return outStream << ProString { ANSI::Yellow   , "[WARN]" } << " : " ;
        case LogLevel::ERR : return outStream << ProString { ANSI::Red      , "[ERRO]" } << " : " ;
        default:             return outStream << ProString { ANSI::EX_Black , "[UNKN]" } << " : " ;
    }
}

void _Log(LogLevel logLevel, const ProString& message, const ProString& context) noexcept
{
    std::cout << '\n' << context << logLevel << message;
}

Logger::Logger(const ProString& logContext)
    : _logContext(logContext.GetParsedString())
{}

Logger::Logger(const std::vector<zutil::ProString>& logContextCollection)
{
    std::string combinedContext;

    for (const zutil::ProString& CONTEXT_PORTION : logContextCollection)
        combinedContext += CONTEXT_PORTION.GetParsedString();

    this->_logContext = combinedContext;
}

void Logger::Log(LogLevel logLevel, const ProString& message) noexcept
{
    ::zutil::Log(logLevel, message, {this->GetContext()});
}

void Logger::AddContext(const ProString& context) noexcept { this->_logContext += context.GetParsedString(); }

[[nodiscard]] const std::string& Logger::GetContext() const noexcept { return this->_logContext; }

Operation::Operation(const ProString& operationDescription, bool isVerbose, std::source_location sourceLocation) noexcept
    : _DESCRIPTION     { operationDescription.GetParsedString() }
    , _SOURCE_LOCATION { sourceLocation }
    , _IS_VERBOSE      { isVerbose }
{
    if (_IS_VERBOSE) ::zutil::Log(LogLevel::DBG, {">> {}", _DESCRIPTION});
}

Operation::~Operation() noexcept
{
    if (_IS_VERBOSE) ::zutil::Log(LogLevel::DBG, {"<< {}", _DESCRIPTION});
}

void Operation::_LogFailure(const ProString& message, LogLevel logLevel) const noexcept
{
    static const std::string SOURCE_LOCATION_STRING = ProString{_SOURCE_LOCATION}.GetParsedString();
    ::zutil::Log(logLevel, {"{} {} : {}", SOURCE_LOCATION_STRING, _DESCRIPTION, message});
}

[[noreturn]] void Operation::FailAbort(const ProString& message) const noexcept
{
    this->_LogFailure(message, LogLevel::ERR);
    std::abort();
}

void Operation::FailWarn(const ProString& message) const noexcept { this->_LogFailure(message, LogLevel::WARN); }

} // namespace zutil
