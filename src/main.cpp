#include "log.hpp"

int main(void)
{
    zutil::log::debug("Hello, World {}", 143);
    zutil::log::info("Hello, World {}", 143);
    zutil::log::warn("Hello, World {}", 143);
    zutil::log::error("Hello, World {}", 143);
    return 0;
}
