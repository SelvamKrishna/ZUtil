#pragma once

#include "_pro_string.hpp"
#include "zexport.hpp"

namespace zutil {

#ifdef Z_DISABLE_TESTING
inline constexpr bool DISABLE_TESTING {true};
#else
inline constexpr bool DISABLE_TESTING {false};
#endif

ZUTIL_API void _Test(bool condition, ProString description, ProString contextTag) noexcept;

inline void Test(
    bool condition,
    ProString description,
    ProString contextTag = {"\n[TEST]", ANSI::Blue}
) noexcept
{
    if constexpr (DISABLE_TESTING) return;
    ::zutil::_Test(condition, description, contextTag);
}

struct ZUTIL_API TestSuite final {
private:
    ProString _description;
    size_t _passedCases = 0;
    size_t _failedCases = 0;

    static constexpr bool _IS_DISABLED {DISABLE_TESTING};


    void _LogDescription() const noexcept;
    void _LogSummary()     const noexcept;
    void _LogCaseCount()   const noexcept;

public:
    TestSuite(ProString description) noexcept;

    ~TestSuite() noexcept;

    constexpr TestSuite(TestSuite&&)                 noexcept = default;
    constexpr TestSuite(const TestSuite&)            noexcept = default;
    constexpr TestSuite& operator=(TestSuite&&)      noexcept = default;
    constexpr TestSuite& operator=(const TestSuite&) noexcept = default;

    [[nodiscard]]
    size_t GetPassedCount() const noexcept;

    [[nodiscard]]
    size_t GetFailedCount() const noexcept;

    [[nodiscard]]
    size_t GetTotalCount() const noexcept;

    void AddCase(bool testResult, ProString testDescription) noexcept;
};

} // namespace zutil

#ifndef Z_CND_SPLAT

#define Z_CND_SPLAT(condition) (condition), {"{}", #condition}

#endif
