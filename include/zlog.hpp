#pragma once

#include "_pro_string.hpp"
#include "zexport.hpp"

#include <iostream>
#include <vector>

namespace zutil {

#ifdef Z_DISABLE_LOGGING
inline constexpr bool DISABLE_LOGGING {true};
#else
inline constexpr bool DISABLE_LOGGING {false};
#endif

enum LogLevel : uint8_t { DBG, INFO, WARN, ERR, _COUNT };

ZUTIL_API std::ostream& operator<<(std::ostream& outStream, const LogLevel& logLevel) noexcept;

ZUTIL_API void _Log(LogLevel logLevel, const ProString& message, const ProString& context) noexcept;

inline void Log(LogLevel level, const ProString& message, const ProString& context = {""}) noexcept
{
    if constexpr (!DISABLE_LOGGING) ::zutil::_Log(level, message, context);
}

struct ZUTIL_API Logger {
private:
    std::string _logContext;

protected:
    Logger() = delete;

    explicit Logger(const ProString& logContext);
    explicit Logger(const std::vector<zutil::ProString>& logContextCollection);

    [[nodiscard]] const std::string& GetContext() const noexcept;

    void AddContext(const ProString& context) noexcept;

    void Log(LogLevel logLevel, const ProString& message) noexcept;
};

struct ZUTIL_API Operation {
private:
    const std::string          _DESCRIPTION;
    const std::source_location _SOURCE_LOCATION;
    const bool                 _IS_VERBOSE {false};

    void _LogFailure(const ProString& message, LogLevel logLevel) const noexcept;

public:
    Operation() = delete;

    Operation(
        const ProString& operationDesc,
        bool isVerbose = false,
        std::source_location sourceLocation = std::source_location::current()
    ) noexcept;

    constexpr Operation& operator=(Operation&&)      noexcept = delete;
    constexpr Operation& operator=(const Operation&) noexcept = delete;

    ~Operation() noexcept;

    [[noreturn]] void FailAbort(const ProString& message) const noexcept;

    template<typename ExceptionT>
    [[noreturn]] void FailThrow(ExceptionT&& exceptionMessage) const
    {
        this->_LogFailure(exceptionMessage.what(), LogLevel::ERR);
        throw std::forward<ExceptionT>(exceptionMessage);
    }

    void FailWarn(const ProString& message) const noexcept;
};

} // namespace zutil

#ifndef Z_VAR_SPLAT

#define Z_VAR_SPLAT(variable) \
    "{} = ({})", ::zutil::ProString{::zutil::ANSI::Magenta, #variable}, (variable)

#endif
