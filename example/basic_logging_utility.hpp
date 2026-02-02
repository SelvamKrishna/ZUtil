#include "log.hpp"

namespace zutil::example {

inline void logFnOverview() noexcept
{
    zutil::log::debug("Debug messages");
    zutil::log::info("Information messages");
    zutil::log::warn("Warning messages");
    zutil::log::error("Error messages: ERR_CODE = {}", 404);
}

} // namespace zutil::example
