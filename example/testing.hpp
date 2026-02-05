#include "zassert.hpp"
#include "ztest.hpp"

namespace example {

inline void assertionFn()
{
    int ERR_CODE = 0;

    zutil::assertCnd(ERR_CODE == 0, "Message MUST NOT be displayed");
    zutil::assertCnd(ERR_CODE != 0, "Error code is non-zero");

    zutil::assertCnd(false, "Message MUST be displayed in Debug builds");
    zutil::assertCnd<1>(false, "Message MUST be displayed in both Debug and Release builds");
}

inline void testFn()
{
    zutil::testCase(true, "This test MUST PASS");
    zutil::testCase(false, "This test MUST FAIL");

    int value = 42;

    zutil::testCase(value == 42, "Value is correct: {}", value);
    zutil::testCase(Z_CND_SPLAT(value > 100));
}

struct TestStruct {
    int a;
    double b;

    bool operator==(const TestStruct& other) const noexcept
    {
        return (this->a == other.a) && (this->b == other.b);
    }

    bool operator!=(const TestStruct& other) const noexcept
    {
        return !(*this == other);
    }
};

inline void testSuiteFn()
{
    zutil::TestSuite suite("Example Test Suite");

    TestStruct obj1 {10, 3.14};
    TestStruct obj2 {10, 3.14};
    TestStruct obj3 {20, 2.71};

    suite.addCase(obj1 == obj2, "obj1 equals obj2");
    suite.addCase(Z_CND_SPLAT(obj1 != obj3));
    suite.addCase(obj1 != obj3, "obj1 not equals obj3");
    suite.addCase(std::string("hello") == std::string("hello"), "Strings are equal");
    suite.addCase(3.14 != 2.71, "Pi is not equal to e");
}

} // namespace example
