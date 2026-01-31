#include <log.hpp>

int main(void)
{
    zutils::Log::dbg("Hello, World {}", 13);
    return 0;
}
