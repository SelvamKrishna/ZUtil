#include "zassert.hpp"
#include "ztest.hpp"

namespace example {

inline void BasicAssertion()
{
    int errCode = 0;

    zutil::Assert(errCode == 0, "Message MUST NOT be displayed");
    zutil::Assert(Z_CND_SPLAT(errCode != 0));
    zutil::Assert<1>(false, "Displayed in both Debug and Release builds");
}

inline void UnitTesting()
{
    zutil::Test(true, "This test MUST PASS");
    zutil::Test(false, "This test MUST FAIL");

    int value = 42;

    zutil::Test(value == 42, {"Value is correct: {}", value});
    zutil::Test(Z_CND_SPLAT(value > 100));
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

inline void SuiteTesting()
{
    zutil::TestSuite suite("Example Test Suite");

    TestStruct objA {10, 3.14};
    TestStruct objB {10, 3.14};
    TestStruct objC {20, 2.71};

    suite.AddCase(objA == objB, "objA equals objB");
    suite.AddCase(Z_CND_SPLAT(objA != objC));
    suite.AddCase(objA != objC, "objA not equals objC");
    suite.AddCase(std::string("hello") == std::string("hello"), "Strings are equal");
    suite.AddCase(3.14 != 2.71, "Pi is not equal to e");
}

} // namespace example
