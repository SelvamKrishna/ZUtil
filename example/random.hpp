#pragma once

#include "../zen/core/test.hpp"
#include "../zen/core/macros.hpp"
#include "../zen/math/random.hpp"

#include <vector>

namespace example
{
    inline void RandomRangeTest() noexcept
    {
        zen::TestSuite test {__PRETTY_FUNCTION__};

        int iVal = zen::random::RangeI32(5, 10);
        test.AddCase(Z_CND_SPLAT(iVal >= 5 && iVal <= 10));

        u32 uVal = zen::random::RangeU32(100, 200);
        test.AddCase(Z_CND_SPLAT(uVal >= 100 && uVal <= 200));

        f32 fVal = zen::random::RangeF32(0.0f, 1.0f);
        test.AddCase(Z_CND_SPLAT(fVal >= 0.0f && fVal <= 1.0f));

        f64 dVal = zen::random::RangeF64(0.0, 1.0);
        test.AddCase(Z_CND_SPLAT(dVal >= 0.0 && dVal <= 1.0));

        f32 unitF = zen::random::UnitF32();
        test.AddCase(Z_CND_SPLAT(unitF >= 0.0f && unitF <= 1.0f));

        f64 unitD = zen::random::UnitF64();
        test.AddCase(Z_CND_SPLAT(unitD >= 0.0 && unitD <= 1.0));

        i32 signI = zen::random::SignI32();
        test.AddCase(Z_CND_SPLAT(signI == -1 || signI == 1));

        f32 signF = zen::random::SignF32();
        test.AddCase(Z_CND_SPLAT(signF == -1.0f || signF == 1.0f));

        bool b = zen::random::Boolean();
        test.AddCase(Z_CND_SPLAT(b == true || b == false));

        bool c = zen::random::Chance(0.5f);
        test.AddCase(Z_CND_SPLAT(c == true || c == false));

        usize idx = zen::random::Index(5);
        test.AddCase(Z_CND_SPLAT(idx < 5));
    }

    inline void RandomShuffleTest() noexcept
    {
        zen::TestSuite test {__PRETTY_FUNCTION__};

        std::vector<int> shuffleVec {1, 2, 3, 4, 5};
        zen::random::Shuffle(shuffleVec.begin(), shuffleVec.end());
        test.AddCase(Z_CND_SPLAT(shuffleVec.size() == 5));
    }

    inline void RandomChoiceTest() noexcept
    {
        zen::TestSuite test {__PRETTY_FUNCTION__};

        std::vector<int> vec {1, 2, 3, 4, 5};
        int val = zen::random::Choice(vec);
        test.AddCase(Z_CND_SPLAT(val >= 1 && val <= 5));

        const std::vector<int> constVec {10, 20, 30};
        int constVal = zen::random::Choice(constVec);
        test.AddCase(Z_CND_SPLAT(constVal == 10 || constVal == 20 || constVal == 30));

        int initVal = zen::random::Choice({100, 200, 300});
        test.AddCase(Z_CND_SPLAT(initVal == 100 || initVal == 200 || initVal == 300));

        std::vector<int> values {1, 2, 3};
        std::vector<int> weights {1, 0, 0};
        int weightedVal = zen::random::WeightedChoice(values, weights);
        test.AddCase(Z_CND_SPLAT(weightedVal == 1));

        int weightedInitVal = zen::random::WeightedChoice({10, 20, 30}, {0, 0, 1});
        test.AddCase(Z_CND_SPLAT(weightedInitVal == 30));
    }

} // namespace example
