#pragma once

#include "zansi.hpp"

#include <format>
#include <iostream>

namespace zutil {

#ifdef Z_DISABLE_TESTING
inline constexpr bool DISABLE_TESTING {true};
#else
inline constexpr bool DISABLE_TESTING {false};
#endif

template <typename... Args>
inline void testCase(bool condition, const std::format_string<Args...> f_str, Args&&... args) noexcept
{
    if constexpr (DISABLE_TESTING) return;

    std::cout
        << "\n"
        << ANSIString{ANSI::Blue, "[TEST]"}
        << ((condition) ? ANSIString{ANSI::Green, "[PASS]"} : ANSIString{ANSI::Red, "[FAIL]"})
        << " : "
        << std::format(f_str, std::forward<Args>(args)...)
    ;
}

class TestUnit final {
private:
    bool _case_output;

public:
    TestUnit(bool case_output) noexcept : _case_output(case_output) {}
    ~TestUnit() noexcept = default;

    constexpr TestUnit(TestUnit&&)                 noexcept = default;
    constexpr TestUnit(const TestUnit&)            noexcept = default;
    constexpr TestUnit& operator=(TestUnit&&)      noexcept = default;
    constexpr TestUnit& operator=(const TestUnit&) noexcept = default;

    template <typename LHS, typename RHS>
    [[nodiscard]]
    static TestUnit fromEq(LHS lhs, RHS rhs)
    {
        return TestUnit(lhs == rhs);
    }

    template <typename LHS, typename RHS>
    [[nodiscard]]
    static TestUnit fromNeq(LHS lhs, RHS rhs)
    {
        return TestUnit(lhs != rhs);
    }

    template <typename... Args>
    void log(const std::format_string<Args...> f_str, Args&&... args) noexcept
    {
        testCase(_case_output, f_str, std::forward<Args>(args)...);
    }
};

} // namespace zutil
