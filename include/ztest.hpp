#pragma once

#include "_pro_string.hpp"

namespace zutil {

#ifdef Z_DISABLE_TESTING
inline constexpr bool DISABLE_TESTING {true};
#else
inline constexpr bool DISABLE_TESTING {false};
#endif

void _test(bool condition, ProString description, ProString prefix) noexcept;

inline void test(bool condition, ProString description, ProString prefix = {"\n[TEST]", ANSI::Blue}) noexcept
{
    if constexpr (DISABLE_TESTING) return;
    _test(condition, description, prefix);
}

class TestSuite final {
private:
    ProString _description;
    size_t _passed_cases = 0;
    size_t _failed_cases = 0;

    static constexpr bool _IS_DISABLED {DISABLE_TESTING};

    void _logDescription() const noexcept;
    void _logSummary() const noexcept;
    void _logCaseCount() const noexcept;

public:
    TestSuite(ProString description) noexcept;

    ~TestSuite() noexcept;

    constexpr TestSuite(TestSuite&&)                 noexcept = default;
    constexpr TestSuite(const TestSuite&)            noexcept = default;
    constexpr TestSuite& operator=(TestSuite&&)      noexcept = default;
    constexpr TestSuite& operator=(const TestSuite&) noexcept = default;

    void addCase(const bool test_result, ProString description) noexcept;
};

} // namespace zutil

#ifndef Z_CND_SPLAT

#define Z_CND_SPLAT(cnd) (cnd), {"{}", #cnd}

#endif
