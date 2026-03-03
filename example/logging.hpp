#pragma once

#include "zlog.hpp"

namespace example
{

    inline void BasicLogging() noexcept
    {
        zutil::Log(zutil::DBG, "Debug messages");
        zutil::Log(zutil::INFO, "Information messages");
        zutil::Log(zutil::WARN, "Warning messages");

        int errCode = 404;

        if (errCode > 0)
            zutil::Log(zutil::ERR, {"Error messages: ERR_CODE = {}", errCode});
    }

    class App : public zutil::Logger
    {
    private:
        bool _isRunning = false;

    public:
        App() : zutil::Logger({
            zutil::ProString {zutil::ANSI::Magenta, "[SYS]"},
            zutil::ProString {zutil::ANSI::Magenta, "[APP]"},
        })
        {
            this->Log(zutil::INFO, "Initialized");
        }

        void Run()
        {
            if (this->_isRunning)
                return this->Log(zutil::WARN, "Run function called multiple times.");

            this->_isRunning = true;
            this->Log(zutil::INFO, "Running");
        }

        void Operate(int errCode)
        {
            zutil::ScopeDiagnostic op {"", this};

            if (errCode > 0)
                op.FailWarn({"Failed with error code: {}", errCode});

            if (errCode == -1)
                op.FailAbort("Failed with critical error");
        }

        void VerboseOperate(int errCode)
        {
            zutil::ScopeDiagnostic op {"Verbose Operation", this, true};

            if (errCode > 0)
                op.FailWarn({"Failed with error code: {}", errCode});

            if (errCode == -1)
                op.FailAbort("Failed with critical error");
        }

        ~App()
        {
            this->Log(zutil::INFO, "Destroyed");
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
