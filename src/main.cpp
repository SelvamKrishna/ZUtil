#include "log.hpp"

int main(void)
{
    zutils::Log::debug("Hello, World {}", 143);
    return 0;
}
