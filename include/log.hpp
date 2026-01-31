#pragma once

#include "ansi.hpp"

#include <format>
#include <string>
#include <string_view>
#include <iostream>

namespace zutils {

class LogString {
protected:
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

    [[nodiscard]]
    const std::string& str() const noexcept;

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

class ColorString final : public LogString {
private:
    ANSI _ansi { ANSI::Reset };

public:
    ColorString(const char* str) noexcept;

    ColorString(ANSI ansi, const char* str) noexcept;

    template <typename... Args>
    ColorString(const std::format_string<Args...> f_str, Args&&... arg)
        : LogString { f_str, arg... }
    {}

    template <typename... Args>
    ColorString(ANSI ansi, const std::format_string<Args...> f_str, Args&&... arg)
        : LogString { f_str, arg... }
        , _ansi {ansi}
    {}

    ~ColorString() noexcept = default;

    constexpr ColorString(ColorString&&)                 noexcept = default;
    constexpr ColorString(const ColorString&)            noexcept = default;
    constexpr ColorString& operator=(ColorString&&)      noexcept = default;
    constexpr ColorString& operator=(const ColorString&) noexcept = default;

    [[nodiscard]]
    ANSI getColor() const noexcept;

    void setColor(ANSI ansi_code) noexcept;

    friend std::ostream& operator<<(std::ostream& os, const ColorString& log_str) noexcept;
};

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

    static void _writeMsg(LogLevel log_lvl, const LogString& log_str) noexcept;

public:
    static void debugMsg(const LogString& log_str) noexcept;

    static void infoMsg(const LogString& log_str) noexcept;

    static void warnMsg(const LogString& log_str) noexcept;

    static void errorMsg(const LogString& log_str) noexcept;
};

} // namespace zutils
