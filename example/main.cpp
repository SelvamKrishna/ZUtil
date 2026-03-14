#include "../zen_prelude.hpp"      // IWYU pragma: keep
#include "../example/logging.hpp" // IWYU pragma: keep
#include "../example/testing.hpp" // IWYU pragma: keep
#include "../example/buffer.hpp"  // IWYU pragma: keep
#include "../example/random.hpp"  // IWYU pragma: keep

#include <iostream>

#define _Z_SHOWCASE_LOGGING 0
#define _Z_SHOWCASE_TESTING 0
#define _Z_TEST_BUFFER  0
#define _Z_TEST_RANDOM  1

void TestExamples(void)
{
#if _Z_SHOWCASE_LOGGING
    example::BasicLogging();
    example::LoggerClass();
    example::ScopeDiagnosticOverview();
#endif
#if _Z_SHOWCASE_TESTING
    // example::BasicAssertion(); // Uncomment to test assertion failure
    example::UnitTesting();
    example::SuiteTesting();
#endif
#if _Z_TEST_BUFFER
    example::DoubleBuffer();
    example::FastAccessBuffer();
    Z_TODO("Test: IteratorWrapper");
    Z_TODO("Test: ObjectPolol");
    example::SparseSetInsertion();
#endif
#if _Z_TEST_RANDOM
    example::RandomChoiceTest();
    example::RandomRangeTest();
    example::RandomShuffleTest();
#endif
}

void Playground(void)
{
}

int main(void)
{
    Z_ON_DBG std::cout << "\n---Test Start---\n";
#if 1
    TestExamples();
#else
    Playground();
#endif
    Z_ON_DBG std::cout << "\n---Test End---\n";
}
