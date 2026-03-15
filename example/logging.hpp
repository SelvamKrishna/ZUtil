#pragma once

#include "../zen/core/logger.hpp"

namespace example {

    inline void BasicLogging() noexcept
    {
        zen::core::Log(zen::core::DBG, "Debug messages");
        zen::core::Log(zen::core::INFO, "Information messages");
        zen::core::Log(zen::core::WARN, "Warning messages");

        int errCode = 404;

        if (errCode > 0)
            zen::core::Log(zen::core::ERR, {"Error messages: ERR_CODE = {}", errCode});
    }

    class App : public zen::core::Logger {
    private:
        bool _isRunning = false;

    public:
        App() : zen::core::Logger ({
            zen::core::ProString {zen::core::ANSI::Magenta, "[SYS]"},
            zen::core::ProString {zen::core::ANSI::Magenta, "[APP]"},
        })
        {
            this->Log(zen::core::INFO, "Initialized");
        }

        void Run()
        {
            if (this->_isRunning)
                return this->Log(zen::core::WARN, "Run function called multiple times.");

            this->_isRunning = true;
            this->Log(zen::core::INFO, "Running");
        }

        void Operate(int errCode)
        {
            zen::core::ScopeDiagnostic op {"", this};
            if (errCode > 0) op.FailWarn({"Failed with error code: {}", errCode});
            if (errCode == -1) op.FailAbort("Failed with critical error");
        }

        void VerboseOperate(int errCode)
        {
            zen::core::ScopeDiagnostic op {"Verbose Operation", this, true};
            if (errCode > 0) op.FailWarn({"Failed with error code: {}", errCode});
            if (errCode == -1) op.FailAbort("Failed with critical error");
        }

        ~App() { this->Log(zen::core::INFO, "Destroyed"); }
    };

    inline void LoggerClass()
    {
        App app;
        app.Run();
        app.Run();
    }

    inline void ScopeDiagnosticOverview()
    {
        App app;
        app.Operate(0);
        app.Operate(404);
        app.VerboseOperate(0);
        app.VerboseOperate(404);
        // app.VerboseOperate(-1); // This will cause the program to abort
    }

} // namespace example
