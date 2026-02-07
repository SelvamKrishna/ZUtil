#pragma once

#include "zansi.hpp"

#include <format>
#include <ostream>
#include <string>
#include <source_location>

namespace zutil {

class ProString {
private:
    zutil::ANSI _ansi { ANSI::Reset };
    std::string _str;

public:
    ProString() noexcept = default;

    ProString(std::string_view str, zutil::ANSI ansi = zutil::ANSI::Reset) noexcept;

    ProString(const char* str, zutil::ANSI ansi = zutil::ANSI::Reset) noexcept;

    ProString(const std::source_location& loc) noexcept;

    template <typename... Args>
    ProString(const std::format_string<Args...> f_str, Args&&... arg)
        : _str { std::format(f_str, std::forward<Args>(arg)...) }
    {}

    template <typename... Args>
    ProString(zutil::ANSI ansi, const std::format_string<Args...> f_str, Args&&... arg)
        : _ansi { ansi }
        , _str  { std::format(f_str, std::forward<Args>(arg)...) }
    {}

    ~ProString() noexcept = default;

    ProString(ProString&&)                 noexcept = default;
    ProString(const ProString&)            noexcept = default;
    ProString& operator=(ProString&&)      noexcept = default;
    ProString& operator=(const ProString&) noexcept = default;

    void clear() noexcept;

    [[nodiscard]]
    zutil::ANSI getColor() const noexcept;

    void setColor(zutil::ANSI ansi_code) noexcept;

    [[nodiscard]]
    const std::string& getString() const noexcept;

    void setString(std::string_view text) noexcept;

    [[nodiscard]]
    std::string getParsedString() const noexcept;

    friend std::ostream& operator<<(std::ostream& os, const ProString& color_str) noexcept;
};

} // namespace zutil

template <>
struct std::formatter<zutil::ProString> {
    constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

    auto format(const zutil::ProString &pro_str, std::format_context &ctx) const
    {
        return std::format_to(ctx.out(), "{}", pro_str.getParsedString());
    }
};
