#include "_pro_string.hpp"
#include "ztest.hpp"

#include <iostream>

namespace zutil {

void _test(bool condition, ProString description, ProString prefix) noexcept
{
    static const ProString TAGS[2] {
        { ANSI::Red   , "[FAIL]" },
        { ANSI::Green , "[PASS]" },
    };

    std::cout << prefix << TAGS[condition] << " : " << description;
}

void TestSuite::_logDescription() const noexcept
{
    std::cout << '\n' << ProString{ANSI::Blue, "[TEST][SUITE]"} << " : " << _description;
}

void TestSuite::_logSummary() const noexcept
{
    std::cout << '\n' << ProString{ANSI::Blue, "[TEST][SUITE]"};
    this->_logCaseCount();
}

void TestSuite::_logCaseCount() const noexcept
{
    std::cout
        << "\n\tPassed Cases : " << _passed_cases
        << "\n\tFailed Cases : " << _failed_cases
        << "\n\tTotal Cases  : " << (_passed_cases + _failed_cases)
        << '\n';
    ;
}

TestSuite::TestSuite(ProString description) noexcept
    : _description {description}
{
    if constexpr (_IS_DISABLED) return;
    _logDescription();
}

TestSuite::~TestSuite() noexcept
{
    if constexpr (_IS_DISABLED) return;
    _logSummary();
}

void TestSuite::addCase(const bool test_result, ProString description) noexcept
{
    ::zutil::test(test_result, description, {"\n\t"});
    (test_result) ? ++_passed_cases : ++_failed_cases;
}

};
