#include "../example/logging.hpp"
#include "../example/testing.hpp"

int main(void)
{
    std::cout << "Running main application..." << '\n';

    example::logFn();
    example::loggerClass();

    // example::assertionFn(); // Uncomment to test assertion failure
    example::testFn();
    example::testSuiteFn();

    return 0;
}
