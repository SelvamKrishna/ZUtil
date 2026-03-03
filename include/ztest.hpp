#pragma once

#include "_export.hpp"
#include "_pro_string.hpp"

namespace zutil
{

#ifdef Z_DISABLE_TESTING
    inline constexpr bool DISABLE_TESTING {true};
#else
    inline constexpr bool DISABLE_TESTING {false};
#endif

    ZUTIL_API void _Test(bool condition, const ProString& description, const ProString& contextTag) noexcept;

    inline void Test(
        bool condition,
        const ProString& description,
        const ProString& contextTag = {"\n[TEST]", ANSI::Blue}
    ) noexcept
    {
        if constexpr (DISABLE_TESTING) return;
        ::zutil::_Test(condition, description, contextTag);
    }

    struct ZUTIL_API TestSuite final
    {
    private:
        std::string _description;
        size_t      _passedCases { 0 };
        size_t      _failedCases { 0 };

        static constexpr bool _IS_DISABLED {DISABLE_TESTING};

        void _LogDescription() const noexcept;
        void _LogSummary()     const noexcept;
        void _LogCaseCount()   const noexcept;

    public:
        TestSuite(const ProString& description) noexcept;

        ~TestSuite() noexcept;

        [[nodiscard]] size_t GetPassedCount() const noexcept;
        [[nodiscard]] size_t GetFailedCount() const noexcept;
        [[nodiscard]] size_t GetTotalCount()  const noexcept;

        void AddCase(bool testResult, const ProString& testDescription) noexcept;
    };

} // namespace zutil
