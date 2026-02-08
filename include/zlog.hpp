#pragma once

#include "_pro_string.hpp"
#include "zexport.hpp"

#include <iostream>
#include <vector>

namespace zutil {

enum LogLevel : uint8_t { DBG, INFO, WARN, ERR };

ZUTIL_API std::ostream& operator<<(std::ostream& os, const LogLevel& log_lvl) noexcept;

ZUTIL_API void _log(LogLevel level, ProString message) noexcept;

#ifdef Z_DISABLE_LOGGING
inline constexpr bool DISABLE_LOGGING {true};
#else
inline constexpr bool DISABLE_LOGGING {false};
#endif

inline void log(LogLevel level, ProString message) noexcept
{
    if constexpr (!DISABLE_LOGGING) _log(level, message);
}

class ZUTIL_API Logger {
private:
    std::string _log_prefix;

protected:
    Logger() = delete;

    explicit Logger(ProString log_prefix);

    explicit Logger(std::vector<zutil::ProString> log_parts);

    constexpr Logger(Logger&&)                 noexcept = default;
    constexpr Logger(const Logger&)            noexcept = default;
    constexpr Logger& operator=(Logger&&)      noexcept = default;
    constexpr Logger& operator=(const Logger&) noexcept = default;

    ~Logger() = default;

    void addPrefix(const std::string_view prefix) noexcept;

    [[nodiscard]]
    const std::string& getPrefix() const noexcept;

    void log(LogLevel level, ProString message) noexcept;
};

class ZUTIL_API Operation {
private:
    const std::string _OP_NAME;
    const bool _TRACE {false};

public:
    Operation() = delete;

    Operation(ProString op_name, bool trace = false) noexcept;

    constexpr Operation(Operation&&)                 noexcept = default;
    constexpr Operation(const Operation&)            noexcept = default;
    constexpr Operation& operator=(Operation&&)      noexcept = delete;
    constexpr Operation& operator=(const Operation&) noexcept = delete;

    ~Operation() noexcept;
};

} // namespace zutil

#ifndef Z_VAR_SPLAT

#define Z_VAR_SPLAT(var) \
    "{} = ({})", ::zutil::ProString{::zutil::ANSI::Magenta, #var}, (var)

#endif
