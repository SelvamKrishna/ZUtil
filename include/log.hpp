#pragma once

#include "ansi.hpp" // IWYU pragma: keep

#include <format>
#include <iostream>
#include <vector>

namespace zutil {

enum LogLevel : uint8_t { DBG, INFO, WARN, ERR };

std::ostream& operator<<(std::ostream& os, const LogLevel& log_lvl) noexcept;

#ifdef Z_DISABLE_LOGGING
inline constexpr bool DISABLE_LOGGING {true};
#else
inline constexpr bool DISABLE_LOGGING {false};
#endif

template <LogLevel Level = LogLevel::DBG, typename... Args>
inline void log(const std::format_string<Args...> f_str, Args&&... args) noexcept
{
    if constexpr (DISABLE_LOGGING) return;
    constexpr std::ostream& os = (Level == LogLevel::ERR || Level == LogLevel::WARN) ? std::cerr : std::cout;
    os << '\n' << Level << std::format(f_str, std::forward<Args>(args)...);
}

template <LogLevel Level = LogLevel::DBG, typename... Args>
inline void logIf(bool condition, const std::format_string<Args...> f_str, Args&&... args) noexcept
{
    if (!condition) return;
    zutil::log<Level>(f_str, std::forward<Args>(args)...);
}

class Logger {
private:
    std::string _log_prefix;

public:
    Logger() = delete;

    explicit Logger(const std::string_view log_prefix);

    template <typename... Args>
    explicit Logger(const std::format_string<Args...> f_str, Args&&... args) noexcept
        : _log_prefix(std::format(f_str, std::forward<Args>(args)...))
    {}

    explicit Logger(std::vector<std::string> log_parts);

    ~Logger() = default;

    void addPrefix(const std::string_view prefix) noexcept;

    [[nodiscard]]
    const std::string& getPrefix() const noexcept;
};

} // namespace zutil

#ifndef Z_VAR_SPLAT

#define Z_VAR_SPLAT(var) \
    "{} = ({})", ::zutil::ColorString{::zutil::ANSI::Magenta, #var}, (var)

#endif
