#include "log.hpp"
#include "validate.hpp"

namespace zutil::example {

inline void logFn() noexcept
{
    zutil::log::debug("Debug messages");
    zutil::log::info("Information messages");
    zutil::log::warn("Warning messages");
    zutil::log::error("Error messages: ERR_CODE = {}", 404);
}

inline void conditionLogFn() noexcept
{
    int result = 13;
    int err_code = 404;

    zutil::log::debugIf(result > 10, Z_VAR_SPLAT(result));
    zutil::log::infoIf(false, "Message must NOT be displayed");
    zutil::log::warnIf(true, "Message must be displayed");
    zutil::log::errorIf(err_code > 0, "Error messages: ERR_CODE = {}", err_code);
}

inline void assertionFn()
{
    zutil::assertCnd(false, "Message MUST be displayed");
}

} // namespace zutil::example
