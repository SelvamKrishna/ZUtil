#include "../zutil.hpp" // IWYU pragma: keep

#include "../example/logging.hpp"
#include "../example/testing.hpp"

int main(void)
{
    std::cout << "Running main application..." << '\n';

    example::BasicLogging();
    example::LoggerClass();
    example::OperationScopeLogging();
    // example::OperationFailLogging();  // Uncomment to test operation failure
    // example::BasicAssertion();        // Uncomment to test assertion failure
    example::UnitTesting();
    example::SuiteTesting();

    return 0;
}
