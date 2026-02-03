#pragma once

#include <format>
#include <iostream>

namespace zutil {

enum class LogLevel : uint8_t { Debug, Info, Warn, Error };
std::ostream& operator<<(std::ostream& os, const LogLevel& log_lvl) noexcept;

#ifndef Z_DISABLE_LOGGING
    inline constexpr bool DISABLE_LOGGING {false};
#else
    inline constexpr bool DISABLE_LOGGING {true};
#endif

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

} // namespace zutil

#ifndef Z_VAR_SPLAT

#include "ansi.hpp" // IWYU pragma: keep
#define Z_VAR_SPLAT(var) "{} = ({})", ::zutil::ColorString{::zutil::ANSI::Magenta, #var}, (var)

#endif
