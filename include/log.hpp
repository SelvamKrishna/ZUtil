#pragma once

#include <format>
#include <iostream>

namespace zutils {

enum class LogLevel : uint8_t { Debug, Info, Warn, Error };

std::ostream& operator<<(std::ostream& os, const LogLevel& log_lvl) noexcept;

class Log final {
private:
    Log() = default;
    ~Log() = default;

    constexpr Log(Log&&)                 noexcept = delete;
    constexpr Log(const Log&)            noexcept = delete;
    constexpr Log& operator=(Log&&)      noexcept = delete;
    constexpr Log& operator=(const Log&) noexcept = delete;

public:
    template <typename... Args>
    static void debug(const std::format_string<Args...> f_str, Args&&... args) noexcept
    {
        std::cout << LogLevel::Debug << " : " << std::format(f_str, std::forward<Args>(args)...) << "\n";
    }

    template <typename... Args>
    static void info(const std::format_string<Args...> f_str, Args&&... args) noexcept
    {
        std::cout << LogLevel::Info << " : " << std::format(f_str, std::forward<Args>(args)...) << "\n";
    }

    template <typename... Args>
    static void warn(const std::format_string<Args...> f_str, Args&&... args) noexcept
    {
        std::cout << LogLevel::Warn << " : " << std::format(f_str, std::forward<Args>(args)...) << "\n";
    }

    template <typename... Args>
    static void error(const std::format_string<Args...> f_str, Args&&... args) noexcept
    {
        std::cout << LogLevel::Error << " : " << std::format(f_str, std::forward<Args>(args)...) << "\n";
    }
};

} // namespace zutils
