#include "../zutil.hpp" // IWYU pragma: keep

#include "../example/file_handling.hpp" // IWYU pragma: keep
#include "../example/logging.hpp"       // IWYU pragma: keep
#include "../example/testing.hpp"       // IWYU pragma: keep

void Playgrond();
void RunAllTests();

int main(void)
{
    std::cout << "Running main application..." << '\n';

#if 1
    RunAllTests();
#else
    Playgrond();
#endif

    return 0;
}

void RunAllTests()
{
    example::BasicLogging();
    example::LoggerClass();
    example::ScopeDiagnosticOverview();
    // example::BasicAssertion();          // Uncomment to test assertion failure
    example::UnitTesting();
    example::SuiteTesting();
}

void Playgrond()
{

}
