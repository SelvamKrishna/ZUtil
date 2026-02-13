#pragma once

#include "_pro_string.hpp"
#include "zexport.hpp"

#include <iostream>
#include <vector>

namespace zutil {

enum LogLevel : uint8_t { DBG, INFO, WARN, ERR };

ZUTIL_API std::ostream& operator<<(std::ostream& outStream, const LogLevel& logLevel) noexcept;

ZUTIL_API void _Log(LogLevel logLevel, ProString message, std::string context) noexcept;

#ifdef Z_DISABLE_LOGGING
inline constexpr bool DISABLE_LOGGING {true};
#else
inline constexpr bool DISABLE_LOGGING {false};
#endif

inline void Log(LogLevel level, ProString message, std::string context = {}) noexcept
{
    if constexpr (!DISABLE_LOGGING) ::zutil::_Log(level, message, context);
}

class ZUTIL_API Logger {
private:
    std::string _logContext;

protected:
    Logger() = delete;

    explicit Logger(ProString logContext);

    explicit Logger(std::vector<zutil::ProString> logContextCollection);

    constexpr Logger(Logger&&)                 noexcept = default;
    constexpr Logger(const Logger&)            noexcept = default;
    constexpr Logger& operator=(Logger&&)      noexcept = default;
    constexpr Logger& operator=(const Logger&) noexcept = default;

    ~Logger() = default;

    void AddContext(const std::string_view context) noexcept;

    [[nodiscard]]
    const std::string& GetContext() const noexcept;

    void Log(LogLevel logLevel, ProString message) noexcept;
};

class ZUTIL_API Operation {
private:
    const std::string _OPERATION_DESCRIPTION;
    const std::string _SOURCE_LOCATION_STRING;
    const bool _IS_VERBOSE {false};

    void _LogFailure(ProString message, LogLevel logLevel) const noexcept;

public:
    Operation() = delete;

    Operation(
        ProString operationDesc,
        bool isVerbose = false,
        const std::source_location& sourceLocation = std::source_location::current()
    ) noexcept;

    constexpr Operation(Operation&&)                 noexcept = default;
    constexpr Operation(const Operation&)            noexcept = default;
    constexpr Operation& operator=(Operation&&)      noexcept = delete;
    constexpr Operation& operator=(const Operation&) noexcept = delete;

    ~Operation() noexcept;

    [[noreturn]]
    void FailAbort(ProString message) const noexcept;

    [[noreturn]]
    void FailThrow(std::exception exception) const noexcept(false);

    void FailWarn(ProString message) const noexcept;

    template <typename ReturnT>
    [[nodiscard]]
    ReturnT FailReturn(const ReturnT& returnValue, ProString message) const noexcept
    {
        this->FailWarn(message);
        return returnValue;
    }
};

} // namespace zutil

#ifndef Z_VAR_SPLAT

#define Z_VAR_SPLAT(variable) \
    "{} = ({})", ::zutil::ProString{::zutil::ANSI::Magenta, #variable}, (variable)

#endif
