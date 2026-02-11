#include "_pro_string.hpp"
#include "ztest.hpp"

#include <iostream>

namespace zutil {

void _Test(bool condition, ProString description, ProString contextTag) noexcept
{
    static const ProString TEST_TAGS[2] {
        { ANSI::Red   , "[FAIL]" },
        { ANSI::Green , "[PASS]" },
    };

    std::cout << contextTag << TEST_TAGS[condition] << " : " << description;
}

void TestSuite::_LogDescription() const noexcept
{
    std::cout << ProString{ANSI::Blue, "\n[TEST][SUITE]"} << " : " << this->_description;
}

void TestSuite::_LogSummary() const noexcept
{
    std::cout << ProString{ANSI::Blue, "\n[TEST][SUITE]"};
    this->_LogCaseCount();
}

void TestSuite::_LogCaseCount() const noexcept
{
    std::cout
        << "\n\tPassed Cases : " << this->GetPassedCount()
        << "\n\tFailed Cases : " << this->GetFailedCount()
        << "\n\tTotal Cases  : " << this->GetTotalCount()
        << '\n';
    ;
}

TestSuite::TestSuite(ProString description) noexcept
    : _description {description}
{
    if constexpr (_IS_DISABLED) return;
    _LogDescription();
}

TestSuite::~TestSuite() noexcept
{
    if constexpr (_IS_DISABLED) return;
    this->_LogSummary();
}

[[nodiscard]]
size_t TestSuite::GetPassedCount() const noexcept
{
    return this->_passedCases;
}

[[nodiscard]]
size_t TestSuite::GetFailedCount() const noexcept
{
    return this->_failedCases;
}

[[nodiscard]]
size_t TestSuite::GetTotalCount() const noexcept
{
    return this->GetPassedCount() + this->GetFailedCount();
}

void TestSuite::AddCase(const bool testResult, ProString testDescription) noexcept
{
    ::zutil::Test(testResult, testDescription, {"\n\t"});
    (testResult == true) ? this->_passedCases ++ : this->_failedCases ++ ;
}

};
