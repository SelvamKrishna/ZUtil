#ifndef ZEN_BUILD
#define ZEN_BUILD
#endif

#include "_pro_string.hpp"
#include "logger.hpp"

namespace zen::core {

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

    Logger::Logger(const ProString& logContext) : _logContext(logContext.GetParsedString()) {}

    Logger::Logger(const std::vector<ProString>& logContextCollection)
    {
        std::string combinedContext;

        for (const ProString& CONTEXT_PORTION : logContextCollection)
            combinedContext += CONTEXT_PORTION.GetParsedString();

        this->_logContext = combinedContext;
    }

    void Logger::Log(LogLevel logLevel, const ProString& message) const noexcept
    {
        ::zen::core::Log(logLevel, message, {this->GetContext()});
    }

    void Logger::AddContext(const ProString& context) noexcept { this->_logContext += context.GetParsedString(); }

    [[nodiscard]] const std::string& Logger::GetContext() const noexcept { return this->_logContext; }

    ScopeDiagnostic::ScopeDiagnostic(
        const ProString& operationDesc,
        const Logger* classLogger,
        bool isVerbose,
        const std::source_location& sourceLocation
    ) noexcept
        : _DESCRIPTION     { operationDesc.GetString().empty() ? sourceLocation.function_name() : operationDesc.GetParsedString() }
        , _SOURCE_LOCATION { sourceLocation }
        , _LOGGER_PTR      { classLogger }
        , _IS_VERBOSE      { isVerbose }
    {
        if (this->_IS_VERBOSE) this->_LogDescription(">>");
    }

    ScopeDiagnostic::~ScopeDiagnostic() noexcept { if (this->_IS_VERBOSE) this->_LogDescription("<<"); }

    void ScopeDiagnostic::_LogDescription(std::string_view prefix) const noexcept
    {
        (this->_LOGGER_PTR == nullptr)
            ?       ::zen::core::Log(LogLevel::DBG, {"{} {}", prefix, this->_DESCRIPTION})
            : this->_LOGGER_PTR->Log(LogLevel::DBG, {"{} {}", prefix, this->_DESCRIPTION})
        ;
    }

    void ScopeDiagnostic::_LogMessage(LogLevel logLevel, const ProString& message) const noexcept
    {
        static const std::string SOURCE_LOCATION_STRING = ProString{this->_SOURCE_LOCATION}.GetParsedString();

        (this->_LOGGER_PTR == nullptr)
            ?       ::zen::core::Log(logLevel, {"{} {} : {}", SOURCE_LOCATION_STRING, this->_DESCRIPTION, message})
            : this->_LOGGER_PTR->Log(logLevel, {"{} {} : {}", SOURCE_LOCATION_STRING, this->_DESCRIPTION, message})
        ;
    }

    [[noreturn]] void ScopeDiagnostic::FailAbort(const ProString& message) const noexcept
    {
        this->_LogMessage(LogLevel::ERR, message);
        std::abort();
    }

    void ScopeDiagnostic::FailWarn(const ProString& message) const noexcept { this->_LogMessage(LogLevel::WARN, message); }

    void ScopeDiagnostic::Success(const ProString& message) const noexcept { this->_LogMessage(LogLevel::INFO, message); }

} // namespace zen::core
