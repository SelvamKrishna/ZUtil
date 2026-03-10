#ifndef ZEN_BUILD
#define ZEN_BUILD
#endif

#include "_pro_string.hpp"
#include "z_test.hpp"

#include <iostream>

namespace zen
{

    void _Test(bool condition, const ProString& description, const ProString& contextTag) noexcept
    {
        std::cout
            << contextTag
            << (condition ? ProString {ANSI::Green, "[PASS]"} : ProString {ANSI::Red, "[FAIL]"})
            << " : "
            << description
        ;
    }

    void TestSuite::_LogDescription() const noexcept
    {
        std::cout << ProString {ANSI::Blue, "\n[TEST][SUITE]"} << " : " << this->_description;
    }

    void TestSuite::_LogSummary() const noexcept
    {
        std::cout << ProString {ANSI::Blue, "\n[TEST][SUITE]"};
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

    TestSuite::TestSuite(const ProString& description) noexcept : _description {description.GetParsedString()}
    {
        if constexpr (!_IS_DISABLED) this->_LogDescription();
    }

    TestSuite::~TestSuite() noexcept { if constexpr (!_IS_DISABLED) this->_LogSummary(); }

    [[nodiscard]] uint32_t TestSuite::GetPassedCount() const noexcept { return this->_passedCases; }
    [[nodiscard]] uint32_t TestSuite::GetFailedCount() const noexcept { return this->_failedCases; }
    [[nodiscard]] uint32_t TestSuite::GetTotalCount()  const noexcept { return this->GetPassedCount() + this->GetFailedCount(); }

    void TestSuite::AddCase(bool testResult, const ProString& testDescription) noexcept
    {
        this->_passedCases += (testResult == true );
        this->_failedCases += (testResult == false);
        ::zen::Test(testResult, testDescription, {"\n\t"});
    }

}; // namespace zen
