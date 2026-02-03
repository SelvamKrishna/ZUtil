#pragma once

#include <format>
#include <iostream>

namespace zutil {

enum class LogLevel : uint8_t { Debug, Info, Warn, Error };
std::ostream& operator<<(std::ostream& os, const LogLevel& log_lvl) noexcept;

namespace log {

#ifndef Z_DISABLE_LOGGING

template <typename... Args>
inline void debug(const std::format_string<Args...> f_str, Args&&... args) noexcept
{
    std::cout << LogLevel::Debug << std::format(f_str, std::forward<Args>(args)...);
}

template <typename... Args>
inline void info(const std::format_string<Args...> f_str, Args&&... args) noexcept
{
    std::cout << LogLevel::Info << std::format(f_str, std::forward<Args>(args)...);
}

template <typename... Args>
inline void warn(const std::format_string<Args...> f_str, Args&&... args) noexcept
{
    std::cerr << LogLevel::Warn << std::format(f_str, std::forward<Args>(args)...);
}

template <typename... Args>
inline void error(const std::format_string<Args...> f_str, Args&&... args) noexcept
{
    std::cerr << LogLevel::Error << std::format(f_str, std::forward<Args>(args)...);
}

#else

inline void debug(...) noexcept {}
inline void info(...) noexcept {}
inline void warn(...) noexcept {}
inline void error(...) noexcept {}

#endif

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
