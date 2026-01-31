#pragma once

#include <format>
#include <print>

namespace zutils {

class Log final {
private:
    Log() noexcept;
    ~Log() noexcept;

    constexpr Log(Log&&)                 noexcept = delete;
    constexpr Log(const Log&)            noexcept = delete;
    constexpr Log& operator=(Log&&)      noexcept = delete;
    constexpr Log& operator=(const Log&) noexcept = delete;

public:
    template <typename... Args>
    static inline void dbg(const std::format_string<Args...> f_str, Args&&... arg) noexcept
    {
        std::print(f_str, std::forward<Args>(arg)...);
    }

    template <typename... Args>
    static inline void info(const std::format_string<Args...> f_str, Args&&... arg) noexcept
    {
        std::print(f_str, std::forward<Args>(arg)...);
    }

    template <typename... Args>
    static inline void warn(const std::format_string<Args...> f_str, Args&&... arg) noexcept
    {
        std::print(f_str, std::forward<Args>(arg)...);
    }

    template <typename... Args>
    static inline void error(const std::format_string<Args...> f_str, Args&&... arg) noexcept
    {
        std::print(f_str, std::forward<Args>(arg)...);
    }
};

} // namespace zutils
