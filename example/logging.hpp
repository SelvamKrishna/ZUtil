#pragma once

#include "../zen/core/logger.hpp"

namespace example
{

    inline void BasicLogging() noexcept
    {
        zen::Log(zen::DBG, "Debug messages");
        zen::Log(zen::INFO, "Information messages");
        zen::Log(zen::WARN, "Warning messages");

        int errCode = 404;

        if (errCode > 0)
            zen::Log(zen::ERR, {"Error messages: ERR_CODE = {}", errCode});
    }

    class App : public zen::Logger
    {
    private:
        bool _isRunning = false;

    public:
        App() : zen::Logger({
            zen::ProString {zen::ANSI::Magenta, "[SYS]"},
            zen::ProString {zen::ANSI::Magenta, "[APP]"},
        })
        {
            this->Log(zen::INFO, "Initialized");
        }

        void Run()
        {
            if (this->_isRunning)
                return this->Log(zen::WARN, "Run function called multiple times.");

            this->_isRunning = true;
            this->Log(zen::INFO, "Running");
        }

        void Operate(int errCode)
        {
            zen::ScopeDiagnostic op {"", this};

            if (errCode > 0)
                op.FailWarn({"Failed with error code: {}", errCode});

            if (errCode == -1)
                op.FailAbort("Failed with critical error");
        }

        void VerboseOperate(int errCode)
        {
            zen::ScopeDiagnostic op {"Verbose Operation", this, true};

            if (errCode > 0)
                op.FailWarn({"Failed with error code: {}", errCode});

            if (errCode == -1)
                op.FailAbort("Failed with critical error");
        }

        ~App()
        {
            this->Log(zen::INFO, "Destroyed");
        }
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
