#include "../zen_core.hpp" // IWYU pragma: keep

#include "../example/logging.hpp"
#include "../example/testing.hpp"

#include <iostream>

void Playground();
void RunAllTests();

int main(void)
{
    Z_ON_DBG std::cout << "\n---Test Start---\n";

#if 1
    RunAllTests();
#else
    Playground();
#endif

    Z_ON_DBG std::cout << "\n---Test End---\n";
    return 0;
}

void RunAllTests(void)
{
    example::BasicLogging();
    example::LoggerClass();
    example::ScopeDiagnosticOverview();
    // example::BasicAssertion();          // Uncomment to test assertion failure
    example::UnitTesting();
    example::SuiteTesting();

    // example::FastAccessBuffer();
    // example::SparseSetInsertion();
    // example::DoubleBuffer();
}

void Playground(void)
{
}
