#define _Z_SHOWCASE_LOGGING (0)
#define _Z_SHOWCASE_TESTING (0)
#define _Z_TEST_BUFFER      (0)
#define _Z_TEST_RANDOM      (1)
#define _Z_TEST_MATH        (1)

#if _Z_SHOWCASE_LOGGING
#include "../example/logging.hpp" // IWYU pragma: keep
#endif
#if _Z_SHOWCASE_TESTING
#include "../example/testing.hpp" // IWYU pragma: keep
#endif
#if _Z_TEST_BUFFER
#include "../example/buffer.hpp"  // IWYU pragma: keep
#endif
#if _Z_TEST_RANDOM
#include "../example/random.hpp"  // IWYU pragma: keep
#endif
#if _Z_TEST_MATH
#include "../example/math.hpp"    // IWYU pragma: keep
#endif

#include <iostream>

int main(void)
{
    Z_ON_DBG std::cout << "\n--- Test Start ---\n";

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
    example::RandomUniformTest();
    example::RandomShuffleTest();
    example::RandomNormalTest();
    example::RandomDiscreteTest();
#endif
#if _Z_TEST_MATH
    example::AngleBasic();
    example::AngleArithmetic();
    example::Vec2Basic();
    example::Vec2Arithmetic();
    example::Vec2Advanced();
#endif

    Z_ON_DBG std::cout << "\n--- Test End ---\n";
}
