#pragma once

#include <format>
#include <iostream>

namespace zutil {

enum class LogLevel : uint8_t { Debug, Info, Warn, Error };
std::ostream& operator<<(std::ostream& os, const LogLevel& log_lvl) noexcept;

namespace log {

template <typename... Args>
void debug(const std::format_string<Args...> f_str, Args&&... args) noexcept
{
    std::cout << LogLevel::Debug << std::format(f_str, std::forward<Args>(args)...);
}

template <typename... Args>
void info(const std::format_string<Args...> f_str, Args&&... args) noexcept
{
    std::cout << LogLevel::Info << std::format(f_str, std::forward<Args>(args)...);
}

template <typename... Args>
void warn(const std::format_string<Args...> f_str, Args&&... args) noexcept
{
    std::cerr << LogLevel::Warn << std::format(f_str, std::forward<Args>(args)...);
}

template <typename... Args>
void error(const std::format_string<Args...> f_str, Args&&... args) noexcept
{
    std::cerr << LogLevel::Error << std::format(f_str, std::forward<Args>(args)...);
}

template <typename... Args>
void debugIf(bool condition, const std::format_string<Args...> f_str, Args&&... args) noexcept
{
	if (!condition) return;
    std::cout << LogLevel::Debug << std::format(f_str, std::forward<Args>(args)...);
}

template <typename... Args>
void infoIf(bool condition, const std::format_string<Args...> f_str, Args&&... args) noexcept
{
	if (!condition) return;
    std::cout << LogLevel::Info << std::format(f_str, std::forward<Args>(args)...);
}

template <typename... Args>
void warnIf(bool condition, const std::format_string<Args...> f_str, Args&&... args) noexcept
{
	if (!condition) return;
    std::cerr << LogLevel::Warn << std::format(f_str, std::forward<Args>(args)...);
}

template <typename... Args>
void errorIf(bool condition, const std::format_string<Args...> f_str, Args&&... args) noexcept
{
	if (!condition) return;
    std::cerr << LogLevel::Error << std::format(f_str, std::forward<Args>(args)...);
}

} // namespace log

} // namespace zutil
