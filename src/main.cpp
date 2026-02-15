#include "../zutil.hpp" // IWYU pragma: keep

#include "../example/file_handling.hpp" // IWYU pragma: keep
#include "../example/logging.hpp"       // IWYU pragma: keep
#include "../example/testing.hpp"       // IWYU pragma: keep

void Playgrond();
void RunAllTests();

int main(void)
{
    std::cout << "Running main application..." << '\n';

    // RunAllTests();

    Playgrond();

    return 0;
}

void Playgrond()
{

}

void RunAllTests()
{
    example::BasicLogging();
    example::LoggerClass();
    example::OperationScopeLogging();
    // example::OperationFailLogging();  // Uncomment to test operation failure
    // example::BasicAssertion();        // Uncomment to test assertion failure
    example::UnitTesting();
    example::SuiteTesting();
}
