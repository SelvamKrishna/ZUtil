#pragma once

#include "_export.hpp"
#include "zansi.hpp"

#include <format>
#include <ostream>
#include <string>
#include <source_location>

namespace zutil
{

    struct ZUTIL_API ProString
    {
    private:
        zutil::ANSI _ansiCode { ANSI::Reset };
        std::string _string;

    public:
        ProString(std::string_view string, zutil::ANSI ansiCode = zutil::ANSI::Reset) noexcept;

        ProString(const char* string, zutil::ANSI ansiCode = zutil::ANSI::Reset) noexcept;

        template <typename... Args>
        ProString(const std::format_string<Args...> formatString, Args&&... formatArgs)
            : _ansiCode { ANSI::Reset }
            , _string   { std::format(formatString, std::forward<Args>(formatArgs)...) }
        {}

        template <typename... Args>
        ProString(zutil::ANSI ansiCode, const std::format_string<Args...> formatString, Args&&... formatArgs)
            : _ansiCode { ansiCode }
            , _string   { std::format(formatString, std::forward<Args>(formatArgs)...) }
        {}

        ProString(const std::source_location& sourceLocation, bool isVerbose = false) noexcept;

        [[nodiscard]] zutil::ANSI        GetColor()        const noexcept;
        [[nodiscard]] const std::string& GetString()       const noexcept;
        [[nodiscard]] std::string        GetParsedString() const noexcept;

        void SetColor(zutil::ANSI ansiCode) noexcept;
        void SetString(std::string_view string) noexcept;

        void Clear() noexcept;

        friend std::ostream& operator<<(std::ostream& outStream, const ProString& proString) noexcept;
    };

} // namespace zutil

template <>
struct std::formatter<zutil::ProString>
{
    constexpr auto parse(std::format_parse_context &ctx) -> std::format_parse_context::const_iterator { return ctx.begin(); }

    auto format(const zutil::ProString &proString, std::format_context &ctx) const
    {
        return std::format_to(ctx.out(), "{}", proString.GetParsedString());
    }
};
