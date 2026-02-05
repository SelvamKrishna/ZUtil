#include "ztest.hpp"

namespace zutil {

TestSuite::TestSuite(std::string_view description) noexcept
    : _description(description)
{
    _logDescription();
}

void TestSuite::_logDescription() const noexcept
{
    if constexpr (DISABLE_TESTING) return;

    std::cout
        << ANSIString{ANSI::Blue, "\n[TEST][SUMMARY]"}
        << " : "
        << _description
    ;
}

TestSuite::~TestSuite() noexcept
{
    if constexpr (DISABLE_TESTING) return;

    std::cout
        << ANSIString{ANSI::Blue, "\n[TEST][SUMMARY]"}
        << std::format(" : ({} / {})", _passed_cases, _passed_cases + _failed_cases)
        << std::endl
    ;
}

};
