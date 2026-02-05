#pragma once

#include "_pro_string.hpp"

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
        << ProString{ANSI::Blue, "\n[TEST]"}
        << ((condition) ? ProString{ANSI::Green, "[PASS]"} : ProString{ANSI::Red, "[FAIL]"})
        << " : "
        << std::format(f_str, std::forward<Args>(args)...)
    ;
}

class TestSuite final {
private:
    std::string _description;
    size_t _passed_cases = 0;
    size_t _failed_cases = 0;

    void _logDescription() const noexcept;

public:
    TestSuite(std::string_view description) noexcept;

    template <typename... Args>
    TestSuite(const std::format_string<Args...> f_str, Args&&... args) noexcept
        : _description(std::format(f_str, std::forward<Args>(args)...))
    {
        _logDescription();
    }

    ~TestSuite() noexcept;

    constexpr TestSuite(TestSuite&&)                 noexcept = default;
    constexpr TestSuite(const TestSuite&)            noexcept = default;
    constexpr TestSuite& operator=(TestSuite&&)      noexcept = default;
    constexpr TestSuite& operator=(const TestSuite&) noexcept = default;

    template <typename... Args>
    void addCase(const bool test_result, const std::format_string<Args...> f_str, Args&&... args) noexcept
    {
        ::zutil::testCase(test_result, f_str, std::forward<Args>(args)...);
        (test_result) ? ++_passed_cases : ++_failed_cases;
    }
};

} // namespace zutil

#ifndef Z_CND_SPLAT

#define Z_CND_SPLAT(cnd) (cnd), "{}", #cnd

#endif
