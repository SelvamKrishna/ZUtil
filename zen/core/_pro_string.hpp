#pragma once

#include "_export.hpp"
#include "_ansi.hpp"

#include <format>
#include <ostream>
#include <string>
#include <source_location>

namespace zen::core {

    /// ---
    /// @brief String wrapper with ANSI color support.
    /// `ProString` encapsulates a `std::string` with an associated ANSI color code.
    /// ---
    struct ZEN_API ProString
    {
    private:
        ANSI _ansiCode { ANSI::Reset }; ///< ANSI code for the string
        std::string _string;                   ///< Stored string data

    public:
    // --- Constructos ---

        /// @brief Constructs a `ProString` from a `std::string_view`.
        /// @param string String content
        /// @param ansiCode Optional ANSI color (default: Reset)
        ProString(std::string_view string, ANSI ansiCode = ANSI::Reset) noexcept;

        /// @brief Constructs a `ProString` from a C-style string.
        /// @param string C-style string content
        /// @param ansiCode Optional ANSI color (default: Reset)
        ProString(const char* string, ANSI ansiCode = ANSI::Reset) noexcept;

        /// @brief Constructs a `ProString` using `std::format_string`.
        /// @tparam Args Format argument types
        /// @param formatString Format string
        /// @param formatArgs Arguments to format
        /// @note ANSI color defaults to `Reset`.
        template <typename... Args>
        ProString(const std::format_string<Args...> formatString, Args&&... formatArgs)
            : _ansiCode { ANSI::Reset }
            , _string   { std::format(formatString, std::forward<Args>(formatArgs)...) }
        {}

        /// @brief Constructs a `ProString` with an explicit ANSI color and format string.
        /// @tparam Args Format argument types
        /// @param ansiCode ANSI color to assign
        /// @param formatString Format string
        /// @param formatArgs Arguments to format
        template <typename... Args>
        ProString(ANSI ansiCode, const std::format_string<Args...> formatString, Args&&... formatArgs)
            : _ansiCode { ansiCode }
            , _string   { std::format(formatString, std::forward<Args>(formatArgs)...) }
        {}

        /// @brief Constructs a `ProString` from a source location.
        /// @param sourceLocation Source location (e.g., `std::source_location::current()`)
        /// @param isVerbose Optional flag for verbose formatting (default: false)
        ProString(const std::source_location& sourceLocation, bool isVerbose = false) noexcept;

    // --- Utilities ---

        /// @brief Returns the ANSI color of the string.
        /// @return ANSI code
        [[nodiscard]] ANSI GetColor() const noexcept;

        /// @brief Returns the underlying string.
        /// @return Const reference to the string
        [[nodiscard]] const std::string& GetString() const noexcept;

        /// @brief Returns the formatted string with ANSI escape codes.
        /// @return String ready for terminal output
        [[nodiscard]] std::string GetParsedString() const noexcept;

        /// @brief Sets the ANSI color for the string.
        /// @param ansiCode ANSI code to assign
        void SetColor(ANSI ansiCode) noexcept;

        /// @brief Sets the string content.
        /// @param string New string content
        void SetString(std::string_view string) noexcept;

        /// @brief Clears the string and resets the ANSI color.
        void Clear() noexcept;

        /// @brief Stream insertion operator.
        /// Inserts the string into the output stream with ANSI color applied.
        /// @param outStream Output stream
        /// @param proString ProString to insert
        /// @return Reference to the output stream
        friend std::ostream& operator<<(std::ostream& outStream, const ProString& proString) noexcept;
    };

} // namespace zen::core

/// @brief Formatter specialization for `zen::core::ProString` to support `std::format`.
/// Allows `ProString` instances to be used in `std::format` or `std::format_to`.
template <>
struct std::formatter<zen::core::ProString>
{
    constexpr auto parse(std::format_parse_context &ctx) -> std::format_parse_context::const_iterator { return ctx.begin(); }

    auto format(const zen::core::ProString &proString, std::format_context &ctx) const
    {
        return std::format_to(ctx.out(), "{}", proString.GetParsedString());
    }
};
