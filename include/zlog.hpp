#pragma once

#include "_pro_string.hpp"

#include <iostream>
#include <vector>

namespace zutil {

enum LogLevel : uint8_t { DBG, INFO, WARN, ERR };

std::ostream& operator<<(std::ostream& os, const LogLevel& log_lvl) noexcept;

void _log(LogLevel level, ProString message) noexcept;

#ifdef Z_DISABLE_LOGGING
inline constexpr bool DISABLE_LOGGING {true};
#else
inline constexpr bool DISABLE_LOGGING {false};
#endif

inline void log(LogLevel level, ProString message) noexcept
{
    if constexpr (!DISABLE_LOGGING) _log(level, message);
}

class Logger {
private:
    std::string _log_prefix;

protected:
    Logger() = delete;

    explicit Logger(ProString log_prefix);

    explicit Logger(std::vector<zutil::ProString> log_parts);

    ~Logger() = default;

    void addPrefix(const std::string_view prefix) noexcept;

    [[nodiscard]]
    const std::string& getPrefix() const noexcept;

    void log(LogLevel level, ProString message) noexcept;
};

} // namespace zutil

#ifndef Z_VAR_SPLAT

#define Z_VAR_SPLAT(var) \
    "{} = ({})", ::zutil::ProString{::zutil::ANSI::Magenta, #var}, (var)

#endif
