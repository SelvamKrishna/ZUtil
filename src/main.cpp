#include "log.hpp"

int main(void)
{
    zutil::Log::debug("Hello, World {}", 143);
    zutil::Log::info("Hello, World {}", 143);
    zutil::Log::warn("Hello, World {}", 143);
    zutil::Log::error("Hello, World {}", 143);
    return 0;
}
