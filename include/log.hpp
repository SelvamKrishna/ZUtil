#pragma once

#include <format>
#include <iostream>

namespace zutil {

/**
 * @enum LogLevel
 * @brief Severity levels for log messages.
 *
 * `LogLevel` represents the classification of a log message.
 * It is primarily used as a prefix when emitting log output.
 */
enum class LogLevel : uint8_t {
    Debug,  /**< Debug-level diagnostic messages */
    Info,   /**< General informational messages */
    Warn,   /**< Warnings indicating potential issues */
    Error   /**< Error messages indicating failures */
};

/**
 * @brief Streams a log level prefix to an output stream.
 *
 * This operator emits a textual representation of the
 * given log level (e.g. `[INFO]`, `[WARN]`).
 *
 * @param os      Output stream
 * @param log_lvl Log level to emit
 * @return Reference to the output stream
 */
std::ostream& operator<<(std::ostream& os, const LogLevel& log_lvl) noexcept;

/**
 * @namespace zutil::log
 * @brief Lightweight logging functions.
 *
 * This namespace provides a minimal, header-only logging
 * interface built on top of `std::format` and standard
 * output streams.
 *
 * @note These functions perform eager formatting.
 */
namespace log {

/**
 * @brief Emits a debug-level log message.
 *
 * Formats the message using `std::format` and writes it
 * to `std::cout` with a debug severity prefix.
 *
 * @tparam Args Format argument types
 * @param f_str Format string
 * @param args  Format arguments
 *
 * @note Intended for development and diagnostics.
 */
template <typename... Args>
void debug(const std::format_string<Args...> f_str, Args&&... args) noexcept
{
    std::cout << LogLevel::Debug << std::format(f_str, std::forward<Args>(args)...);
}

/**
 * @brief Emits an informational log message.
 *
 * Formats the message using `std::format` and writes it
 * to `std::cout` with an info severity prefix.
 *
 * @tparam Args Format argument types
 * @param f_str Format string
 * @param args  Format arguments
 */
template <typename... Args>
void info(const std::format_string<Args...> f_str, Args&&... args) noexcept
{
    std::cout << LogLevel::Info << std::format(f_str, std::forward<Args>(args)...);
}

/**
 * @brief Emits a warning-level log message.
 *
 * Formats the message using `std::format` and writes it
 * to `std::cerr` with a warning severity prefix.
 *
 * @tparam Args Format argument types
 * @param f_str Format string
 * @param args  Format arguments
 *
 * @note Warnings indicate recoverable or non-fatal issues.
 */
template <typename... Args>
void warn(const std::format_string<Args...> f_str, Args&&... args) noexcept
{
    std::cerr << LogLevel::Warn << std::format(f_str, std::forward<Args>(args)...);
}

/**
 * @brief Emits an error-level log message.
 *
 * Formats the message using `std::format` and writes it
 * to `std::cerr` with an error severity prefix.
 *
 * @tparam Args Format argument types
 * @param f_str Format string
 * @param args  Format arguments
 *
 * @note Errors indicate failures or unrecoverable conditions.
 */
template <typename... Args>
void error(const std::format_string<Args...> f_str, Args&&... args) noexcept
{
    std::cerr << LogLevel::Error << std::format(f_str, std::forward<Args>(args)...);
}

} // namespace log

} // namespace zutil
