#pragma once

#include "_export.hpp"
#include "_pro_string.hpp"

namespace zen
{

#ifdef Z_DISABLE_TESTING
    inline constexpr bool DISABLE_TESTING {true};
#else
    inline constexpr bool DISABLE_TESTING {false};
#endif

    /// @brief Internal testing implementation.
    /// Evaluates a condition and logs the result with a description and context tag.
    /// This function is intended to be called through zen::Test().
    /// @param condition Result of the test condition.
    /// @param description Description of the test.
    /// @param contextTag Optional context tag used for grouping or labeling tests.
    ZEN_API void _Test(bool condition, const ProString& description, const ProString& contextTag) noexcept;

    /// @brief Evaluates a test condition and logs the result.
    /// If testing is disabled via `Z_DISABLE_TESTING`, this function becomes a compile-time no-op.
    /// @param condition Boolean expression representing the test result.
    /// @param description Description of the test.
    /// @param contextTag Optional context tag used for grouping tests.
    inline void Test(
        bool condition,
        const ProString& description,
        const ProString& contextTag = {"\n[TEST]", ANSI::Blue}
    ) noexcept
    {
        if constexpr (DISABLE_TESTING) return;
        ::zen::_Test(condition, description, contextTag);
    }

    /// ---
    /// @brief A collection of related test cases with automatic summary reporting.
    /// `TestSuite` groups multiple test cases and keeps track of how many
    /// passed and failed. When the suite goes out of scope, a summary
    /// of the results is automatically logged.
    /// ---
    struct ZEN_API TestSuite final
    {
    private:
        std::string _description;     ///< Description of the test suite
        uint32_t    _passedCases = 0; ///< Number of passed test cases
        uint32_t    _failedCases = 0; ///< Number of failed test cases

        static constexpr bool _IS_DISABLED {DISABLE_TESTING}; ///< Cached disable flag

        /// @brief Logs the test suite description.
        void _LogDescription() const noexcept;

        /// @brief Logs the summary of test results.
        void _LogSummary() const noexcept;

        /// @brief Logs the total number of executed test cases.
        void _LogCaseCount() const noexcept;

    public:
        /// @brief Constructs a new test suite.
        /// The description is logged when the suite begins execution.
        /// @param description Description of the test suite.
        TestSuite(const ProString& description) noexcept;

        /// @brief Destroys the test suite and prints the test summary.
        /// Automatically logs the total number of tests, passed tests,
        /// and failed tests when the suite goes out of scope.
        ~TestSuite() noexcept;

        /// @return Passed test count.
        [[nodiscard]] uint32_t GetPassedCount() const noexcept;

        /// @return Failed test count.
        [[nodiscard]] uint32_t GetFailedCount() const noexcept;

        /// @return Total test count.
        [[nodiscard]] uint32_t GetTotalCount() const noexcept;

        /// @brief Adds a test case to the suite.
        /// Logs the test result and updates the internal counters.
        /// @param testResult Result of the test condition.
        /// @param testDescription Description of the test case.
        void AddCase(bool testResult, const ProString& testDescription) noexcept;
    };

} // namespace zen
