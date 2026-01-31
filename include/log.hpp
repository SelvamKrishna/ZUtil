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
    LogString(const char* str) noexcept : _str { str } {}

    template <typename... Args>
    LogString(const std::format_string<Args...> f_str, Args&&... arg)
        : _str { std::format(f_str, std::forward<Args>(arg)...) }
    {}

    ~LogString() noexcept = default;

    constexpr LogString(LogString&&)                 noexcept = default;
    constexpr LogString(const LogString&)            noexcept = default;
    constexpr LogString& operator=(LogString&&)      noexcept = default;
    constexpr LogString& operator=(const LogString&) noexcept = default;

    void clear() noexcept
    {
        this->_str.clear();
    }

    inline const std::string& str() const noexcept
    {
        return this->_str;
    }

    inline operator bool() const noexcept
    {
        return !this->_str.empty();
    }

    inline operator std::string_view() const noexcept
    {
        return this->_str;
    }

    friend std::ostream& operator<<(std::ostream& os, const LogString& log_str) noexcept
    {
        os << log_str.str();
        return os;
    }
};

class Log final {
private:
    constexpr Log(Log&&)                 noexcept = delete;
    constexpr Log(const Log&)            noexcept = delete;
    constexpr Log& operator=(Log&&)      noexcept = delete;
    constexpr Log& operator=(const Log&) noexcept = delete;

public:
    static void debugMsg(const LogString& log_str) noexcept
    {
        std::cout << "[DBUG] : " << log_str << "\n";
    }

    static void infoMsg(const LogString& log_str) noexcept
    {
        std::cout << "[INFO] : " << log_str << "\n";
    }

    static void warnMsg(const LogString& log_str) noexcept
    {
        std::cout << "[WARN] : " << log_str << "\n";
    }

    static void errorMsg(const LogString& log_str) noexcept
    {
        std::cout << "[ERRO] : " << log_str << "\n";
    }
};

} // namespace zutils
