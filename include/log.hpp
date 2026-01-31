#pragma once

#include <format>
#include <string>
#include <string_view>
#include <iostream>

namespace zutils {

class LogString final {
private:
    std::string _str;

public:
    LogString(const char* str) noexcept;

    template <typename... Args>
    LogString(const std::format_string<Args...> f_str, Args&&... arg)
        : _str { std::format(f_str, std::forward<Args>(arg)...) }
    {}

    ~LogString() noexcept = default;

    constexpr LogString(LogString&&)                 noexcept = default;
    constexpr LogString(const LogString&)            noexcept = default;
    constexpr LogString& operator=(LogString&&)      noexcept = default;
    constexpr LogString& operator=(const LogString&) noexcept = default;

    void clear() noexcept;

    inline const std::string& str() const noexcept;

    inline operator bool() const noexcept
    {
        return !this->_str.empty();
    }

    inline operator std::string_view() const noexcept
    {
        return this->_str;
    }

    friend std::ostream& operator<<(std::ostream& os, const LogString& log_str) noexcept;
};

class Log final {
private:
    Log() = default;
    ~Log() = default;

    constexpr Log(Log&&)                 noexcept = delete;
    constexpr Log(const Log&)            noexcept = delete;
    constexpr Log& operator=(Log&&)      noexcept = delete;
    constexpr Log& operator=(const Log&) noexcept = delete;

    static void _writeTimestamp() noexcept;

    static void _writeMsg(std::string_view prefix, const LogString& log_str) noexcept;

public:
    static void debugMsg(const LogString& log_str) noexcept;

    static void infoMsg(const LogString& log_str) noexcept;

    static void warnMsg(const LogString& log_str) noexcept;

    static void errorMsg(const LogString& log_str) noexcept;
};

} // namespace zutils
