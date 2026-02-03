#pragma once

#include "ansi.hpp" // IWYU pragma: keep

#include <format>
#include <iostream>
#include <vector>

namespace zutil {

enum class LogLevel : uint8_t { Debug, Info, Warn, Error };
std::ostream& operator<<(std::ostream& os, const LogLevel& log_lvl) noexcept;

inline constexpr bool DISABLE_LOGGING {
    #ifdef Z_DISABLE_LOGGING
        true
    #else
        false
    #endif
};

namespace log {

template <typename... Args>
inline void debug(const std::format_string<Args...> f_str, Args&&... args) noexcept
{
    if constexpr (DISABLE_LOGGING) return;
    std::cout << LogLevel::Debug << std::format(f_str, std::forward<Args>(args)...);
}

template <typename... Args>
inline void info(const std::format_string<Args...> f_str, Args&&... args) noexcept
{
    if constexpr (DISABLE_LOGGING) return;
    std::cout << LogLevel::Info << std::format(f_str, std::forward<Args>(args)...);
}

template <typename... Args>
inline void warn(const std::format_string<Args...> f_str, Args&&... args) noexcept
{
    if constexpr (DISABLE_LOGGING) return;
    std::cerr << LogLevel::Warn << std::format(f_str, std::forward<Args>(args)...);
}

template <typename... Args>
inline void error(const std::format_string<Args...> f_str, Args&&... args) noexcept
{
    if constexpr (DISABLE_LOGGING) return;
    std::cerr << LogLevel::Error << std::format(f_str, std::forward<Args>(args)...);
}

template <typename... Args>
inline void debugIf(bool condition, const std::format_string<Args...> f_str, Args&&... args) noexcept
{
	if (!condition) return;
    zutil::log::debug(f_str, std::forward<Args>(args)...);
}

template <typename... Args>
inline void infoIf(bool condition, const std::format_string<Args...> f_str, Args&&... args) noexcept
{
	if (!condition) return;
    zutil::log::info(f_str, std::forward<Args>(args)...);
}

template <typename... Args>
inline void warnIf(bool condition, const std::format_string<Args...> f_str, Args&&... args) noexcept
{
	if (!condition) return;
    zutil::log::warn(f_str, std::forward<Args>(args)...);
}

template <typename... Args>
inline void errorIf(bool condition, const std::format_string<Args...> f_str, Args&&... args) noexcept
{
	if (!condition) return;
    zutil::log::error(f_str, std::forward<Args>(args)...);
}

} // namespace log

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

    template <typename... Args>
    void debug(const std::format_string<Args...> f_str, Args&&... args) const noexcept
    {
        if constexpr (DISABLE_LOGGING) return;
        std::cout << "\n" << this->_log_prefix << LogLevel::Debug << std::format(f_str, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void info(const std::format_string<Args...> f_str, Args&&... args) const noexcept
    {
        if constexpr (DISABLE_LOGGING) return;
        std::cout << "\n" << this->_log_prefix << LogLevel::Info << std::format(f_str, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void warn(const std::format_string<Args...> f_str, Args&&... args) const noexcept
    {
        if constexpr (DISABLE_LOGGING) return;
        std::cerr << "\n" << this->_log_prefix << LogLevel::Warn << std::format(f_str, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void error(const std::format_string<Args...> f_str, Args&&... args) const noexcept
    {
        if constexpr (DISABLE_LOGGING) return;
        std::cerr << "\n" << this->_log_prefix << LogLevel::Error << std::format(f_str, std::forward<Args>(args)...);
    }
};

} // namespace zutil

#ifndef Z_VAR_SPLAT

#define Z_VAR_SPLAT(var) "{} = ({})", ::zutil::ColorString{::zutil::ANSI::Magenta, #var}, (var)

#endif
