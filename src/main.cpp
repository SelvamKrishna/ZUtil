#include "../example/logging.hpp"

int main(void)
{
    example::logFn();
    example::conditionLogFn();
    // example::assertionFn(); // Uncomment to test assertion failure
    example::testFn();

    return 0;
}
