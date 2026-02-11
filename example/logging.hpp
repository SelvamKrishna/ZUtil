#include "zlog.hpp"

namespace example {

inline void BasicLogging() noexcept
{
    zutil::Log(zutil::DBG, "Debug messages");
    zutil::Log(zutil::INFO, "Information messages");
    zutil::Log(zutil::WARN, "Warning messages");

    int errCode = 404;

    if (errCode > 0)
        zutil::Log(zutil::ERR, {"Error messages: ERR_CODE = {}", errCode});
}

class App : public zutil::Logger {
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

    void run()
    {
        if (this->_isRunning)
            return this->Log(zutil::WARN, "Run function called multiple times.");

        _isRunning = true;
        this->Log(zutil::INFO, "Running");
    }

    ~App()
    {
        this->Log(zutil::INFO, "Destroyed");
    }
};

inline void LoggerClass()
{
    App app;
    app.run();
    app.run();
}

inline void OperationScopeLogging()
{
    zutil::Operation op1("Outer Operation", true);

    {
        zutil::Operation op2("Inner Operation", true);
    }
}

inline void OperationFailLogging()
{
    zutil::Operation op("Failing Operation", true);

    op.FailWarn("This is a warning inside the operation.");
    op.FailThrow(std::runtime_error("This is an exception inside the operation."));
    op.FailAbort("This is a fatal error inside the operation.");
}

} // namespace example
