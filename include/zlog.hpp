#pragma once

#include "_export.hpp"
#include "_pro_string.hpp"

#include <iostream>
#include <vector>

namespace zutil
{
#ifdef Z_DISABLE_LOGGING
    inline constexpr bool DISABLE_LOGGING {true};
#else
    inline constexpr bool DISABLE_LOGGING {false};
#endif

    enum LogLevel : uint8_t { DBG, INFO, WARN, ERR, _COUNT };

    ZUTIL_API std::ostream& operator<<(std::ostream& outStream, const LogLevel& logLevel) noexcept;

    ZUTIL_API void _Log(LogLevel logLevel, const ProString& message, const ProString& context) noexcept;

    inline void Log(LogLevel level, const ProString& message, const ProString& context = {""}) noexcept
    {
        if constexpr (!DISABLE_LOGGING) ::zutil::_Log(level, message, context);
    }

    struct ZUTIL_API Logger
    {
        friend struct ScopeDiagnostic;

    private:
        std::string _logContext;

    protected:
        Logger() = delete;

        explicit Logger(const ProString& logContext);
        explicit Logger(const std::vector<zutil::ProString>& logContextCollection);

        [[nodiscard]] const std::string& GetContext() const noexcept;

        void AddContext(const ProString& context) noexcept;

        void Log(LogLevel logLevel, const ProString& message) const noexcept;
    };

    struct ZUTIL_API ScopeDiagnostic
    {
    private:
        const std::string          _DESCRIPTION;
        const std::source_location _SOURCE_LOCATION;
        const Logger*              _LOGGER_PTR {nullptr};
        const bool                 _IS_VERBOSE {false};

        void _LogDescription(std::string_view prefix) const noexcept;
        void _LogMessage(LogLevel logLevel, const ProString& message) const noexcept;

    public:
        ScopeDiagnostic(
            const ProString& operationDesc = "",
            const Logger* classLogger = nullptr,
            bool isVerbose = false,
            const std::source_location& sourceLocation = std::source_location::current()
        ) noexcept;

        ScopeDiagnostic& operator=(ScopeDiagnostic&&)      noexcept = delete;
        ScopeDiagnostic& operator=(const ScopeDiagnostic&) noexcept = delete;

        ~ScopeDiagnostic() noexcept;

        [[noreturn]] void FailAbort(const ProString& message) const noexcept;

        void FailWarn(const ProString& message) const noexcept;
        void Success (const ProString& message) const noexcept;
    };

} // namespace zutil
