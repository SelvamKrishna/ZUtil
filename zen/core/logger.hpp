#pragma once

#include "_export.hpp"
#include "_pro_string.hpp"

#include <iostream>
#include <vector>

namespace zen
{

#ifdef Z_DISABLE_LOGGING
    inline constexpr bool DISABLE_LOGGING {true};
#else
    inline constexpr bool DISABLE_LOGGING {false};
#endif

    /// @brief Logging severity levels.
    /// Used to categorize log messages according to their importance.
    enum LogLevel : uint8_t
    {
        DBG  = 0, ///< Debug information
        INFO = 1, ///< Informational message
        WARN = 2, ///< Warning condition
        ERR  = 3, ///< Error condition
        _COUNT    ///< Internal count of levels
    };

    /// @brief Stream insertion operator for LogLevel.
    /// @param outStream Output stream.
    /// @param logLevel Log level to print.
    /// @return Reference to the output stream.
    ZEN_API std::ostream& operator<<(std::ostream& outStream, const LogLevel& logLevel) noexcept;

    /// @brief Internal logging implementation.
    /// Outputs a log message with the given severity and context.
    /// @param logLevel Severity level of the message.
    /// @param message Message to log.
    /// @param context Optional contextual information.
    /// @note Intended to be called through zen::Log().
    ZEN_API void _Log(LogLevel logLevel, const ProString& message, const ProString& context) noexcept;

    /// @brief Logs a message with a specified severity level.
    /// If logging is disabled via `Z_DISABLE_LOGGING`, this function
    /// becomes a compile-time no-op.
    /// @param level Log severity level.
    /// @param message Message to output.
    /// @param context Optional contextual information.
    inline void Log(LogLevel level, const ProString& message, const ProString& context = {""}) noexcept
    {
        if constexpr (!DISABLE_LOGGING) ::zen::_Log(level, message, context);
    }

    /// @brief Base class that provides contextual logging.
    /// `Logger` allows derived classes or systems to attach a persistent
    /// context prefix to all log messages. This is useful for identifying
    /// the source of logs such as subsystems, managers, or objects.
    struct ZEN_API Logger
    {
        friend struct ScopeDiagnostic;

    private:
        std::string _logContext; ///< Context prefix applied to log messages

    protected:
        /// @brief Disabled default constructor.
        Logger() = delete;

        /// @brief Constructs a logger with a single context tag.
        /// @param logContext Context label.
        explicit Logger(const ProString& logContext);

        /// @brief Constructs a logger with multiple context tags.
        /// Each element is appended to the context prefix.
        /// @param logContextCollection Collection of context labels.
        explicit Logger(const std::vector<zen::ProString>& logContextCollection);

        /// @brief Returns the stored logging context.
        /// @return Context string.
        [[nodiscard]] const std::string& GetContext() const noexcept;

        /// @brief Appends an additional context tag.
        /// @param context Context label to append.
        void AddContext(const ProString& context) noexcept;

        /// @brief Logs a message using the stored context prefix.
        /// @param logLevel Severity level.
        /// @param message Message to log.
        void Log(LogLevel logLevel, const ProString& message) const noexcept;
    };

    /// ---
    /// @brief RAII diagnostic helper for scoped operations.
    /// Automatically logs diagnostic information about an operation within scope.
    /// It is commonly used to report success or failure of operations along with context
    /// @note The class can optionally attach to a `Logger` instance to
    /// inherit its logging context.
    /// ---
    struct ZEN_API ScopeDiagnostic
    {
    private:
        std::string          _DESCRIPTION;          ///< Description of the operation
        std::source_location _SOURCE_LOCATION;      ///< Source location of invocation
        const Logger*        _LOGGER_PTR {nullptr}; ///< Optional logger context
        bool                 _IS_VERBOSE {false};   ///< Verbose logging flag

        /// @brief Logs the operation description.
        /// @param prefix Text prefix applied to the message.
        void _LogDescription(std::string_view prefix) const noexcept;

        /// @brief Logs a message using the configured context.
        /// @param logLevel Severity level.
        /// @param message Message to log.
        void _LogMessage(LogLevel logLevel, const ProString& message) const noexcept;

    public:
        /// @brief Constructs a scope diagnostic helper.
        /// @param operationDesc Description of the operation being performed.
        /// @param classLogger Optional logger providing context.
        /// @param isVerbose Enables additional verbose logging.
        /// @param sourceLocation Automatically captured source location.
        ScopeDiagnostic(
            const ProString& operationDesc = "",
            const Logger* classLogger = nullptr,
            bool isVerbose = false,
            const std::source_location& sourceLocation = std::source_location::current()
        ) noexcept;

        ScopeDiagnostic& operator=(ScopeDiagnostic&&)      noexcept = delete;
        ScopeDiagnostic& operator=(const ScopeDiagnostic&) noexcept = delete;

        /// @brief Destructor.
        /// May log completion or summary information depending on verbosity
        /// and recorded state.
        ~ScopeDiagnostic() noexcept;

        /// @brief Logs an error message and aborts the process.
        /// Intended for unrecoverable failures.
        /// @param message Error message to log.
        [[noreturn]] void FailAbort(const ProString& message) const noexcept;

        /// @brief Logs a warning indicating operation failure.
        /// @param message Warning message to log.
        void FailWarn(const ProString& message) const noexcept;

        /// @brief Logs a success message for the operation.
        /// @param message Success message to log.
        void Success(const ProString& message) const noexcept;
    };

} // namespace zen
