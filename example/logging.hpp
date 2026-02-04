#include "log.hpp"
#include "validate.hpp"

namespace example {

inline void logFn() noexcept
{
    zutil::log<zutil::DBG>("Debug messages");
    zutil::log<zutil::INFO>("Information messages");
    zutil::log<zutil::WARN>("Warning messages");
    zutil::log<zutil::ERR>("Error messages: ERR_CODE = {}", 404);
}

inline void conditionLogFn() noexcept
{
    int result = 13;
    int err_code = 404;

    zutil::logIf<zutil::DBG>(result > 10, Z_VAR_SPLAT(result));
    zutil::logIf<zutil::INFO>(false, "Message must NOT be displayed");
    zutil::logIf<zutil::WARN>(true, "Message must be displayed");
    zutil::logIf<zutil::ERR>(err_code > 0, "Error messages: ERR_CODE = {}", err_code);
}

inline void assertionFn()
{
    zutil::assertCnd(true, "Message MUST NOT be displayed");
    zutil::assertCnd(false, "Message MUST be displayed");
}

inline void testFn()
{
    zutil::testCase(true, "This test MUST PASS");
    zutil::testCase(false, "This test MUST FAIL");

    int value = 42;

    zutil::testCase(value == 42, "Value is correct: {}", value);
    zutil::testCase(Z_CND_SPLAT(value > 10));
}

} // namespace example
