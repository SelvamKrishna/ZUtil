#include "log.hpp"

namespace zutil::example {

inline void logFnOverview() noexcept
{
    zutil::log::debug("Debug messages");
    zutil::log::info("Information messages");
    zutil::log::warn("Warning messages");
    zutil::log::error("Error messages: ERR_CODE = {}", 404);
}

inline void conditionLogFnOverview() noexcept
{
    log::infoIf(false, "Message must NOT be displayed");
    log::warnIf(true, "Message must be displayed");
    int err_code = 404;
    zutil::log::errorIf(err_code > 0, "Error messages: ERR_CODE = {}", err_code);
}

} // namespace zutil::example
