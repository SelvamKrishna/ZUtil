#include "zlog.hpp"

namespace example {

inline void logFn() noexcept
{
    zutil::log(zutil::DBG, "Debug messages");
    zutil::log(zutil::INFO, "Information messages");
    zutil::log(zutil::WARN, "Warning messages");

    int err_code = 404;

    if (err_code > 0)
        zutil::log(zutil::ERR, {"Error messages: ERR_CODE = {}", err_code});
}

class App : public zutil::Logger {
private:
    bool _is_running = false;

public:
    App() : zutil::Logger({
        zutil::ProString {zutil::ANSI::Magenta, "[SYS]"},
        zutil::ProString {zutil::ANSI::Magenta, "[APP]"},
    })
    {
        this->log(zutil::INFO, "Initialized");
    }

    void run()
    {
        if (this->_is_running)
            return this->log(zutil::WARN, "Run function called multiple times.");
        _is_running = true;
        this->log(zutil::INFO, "Running");
    }

    ~App()
    {
        this->log(zutil::INFO, "Destroyed");
    }
};

inline void loggerClass()
{
    App app;
    app.run();
    app.run();
}

} // namespace example
