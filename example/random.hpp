#pragma once

#include "../zen/core/test.hpp"
#include "../zen/core/macros.hpp"
#include "../zen/math/random.hpp"

#include <numeric>
#include <vector>

namespace example {

    inline void RandomUniformTest() noexcept
    {
        zen::core::TestSuite test {__PRETTY_FUNCTION__};

        int iVal = zen::random::RangeI32(5, 10);
        test.AddCase(Z_CND_SPLAT(iVal >= 5 && iVal <= 10));

        zen::u32 uVal = zen::random::RangeU32(100, 200);
        test.AddCase(Z_CND_SPLAT(uVal >= 100 && uVal <= 200));

        zen::f32 fVal = zen::random::RangeF32(0.0f, 1.0f);
        test.AddCase(Z_CND_SPLAT(fVal >= 0.0f && fVal <= 1.0f));

        zen::f32 unitF = zen::random::UnitF32();
        test.AddCase(Z_CND_SPLAT(unitF >= 0.0f && unitF <= 1.0f));

        zen::f64 unitD = zen::random::UnitF64();
        test.AddCase(Z_CND_SPLAT(unitD >= 0.0 && unitD <= 1.0));

        zen::i32 signI = zen::random::SignI32();
        test.AddCase(Z_CND_SPLAT(signI == -1 || signI == 1));

        zen::f32 signF = zen::random::SignF32();
        test.AddCase(Z_CND_SPLAT(signF == -1.0f || signF == 1.0f));

        bool b = zen::random::Boolean();
        test.AddCase(Z_CND_SPLAT(b == true || b == false));

        bool c = zen::random::Chance(0.5f);
        test.AddCase(Z_CND_SPLAT(c == true || c == false));

        zen::usize idx = zen::random::Index(5);
        test.AddCase(Z_CND_SPLAT(idx < 5));

        std::vector<int> vec {1, 2, 3, 4, 5};
        int val = zen::random::Choice(vec);
        test.AddCase(Z_CND_SPLAT(val >= 1 && val <= 5));

        const std::vector<int> CONST_VEC {10, 20, 30};
        int constVal = zen::random::Choice(CONST_VEC);
        test.AddCase(Z_CND_SPLAT(constVal == 10 || constVal == 20 || constVal == 30));

        int initVal = zen::random::Choice({100, 200, 300});
        test.AddCase(Z_CND_SPLAT(initVal == 100 || initVal == 200 || initVal == 300));
    }

    inline void RandomNormalTest() noexcept
    {
        zen::core::TestSuite test {__PRETTY_FUNCTION__};

        constexpr int SAMPLE_COUNT = 1'000'000;

        constexpr float MEAN      = 10.0f;
        constexpr float STDDEV    = 2.0f;
        constexpr float TOLERANCE = 0.05f;

        std::vector<float> values;
        values.reserve(SAMPLE_COUNT);

        for (int i = 0; i < SAMPLE_COUNT; ++i)
            values.push_back(zen::random::NormalF32(MEAN, STDDEV));

        float sum = std::accumulate(values.begin(), values.end(), 0.0f);
        float sampleMean = sum / SAMPLE_COUNT;

        float variance = 0.0f;
        for (float v : values)
            variance += (v - sampleMean) * (v - sampleMean);

        variance /= SAMPLE_COUNT;

        float sampleStdDev = std::sqrt(variance);


        test.AddCase(Z_CND_SPLAT(std::abs(sampleMean - MEAN) < TOLERANCE));
        test.AddCase(Z_CND_SPLAT(std::abs(sampleStdDev - STDDEV) < TOLERANCE));
    }

    inline void RandomShuffleTest() noexcept
    {
        zen::core::TestSuite test {__PRETTY_FUNCTION__};

        std::vector<int> shuffleVec {1, 2, 3, 4, 5};
        zen::random::Shuffle(shuffleVec.begin(), shuffleVec.end());
        test.AddCase(Z_CND_SPLAT(shuffleVec.size() == 5));
    }

    inline void RandomDiscreteTest() noexcept
    {
        zen::core::TestSuite test {__PRETTY_FUNCTION__};

        std::vector<int> values {1, 2, 3};
        std::vector<int> weights {1, 0, 0};

        int weightedVal = zen::random::WeightedChoice(values, weights);
        test.AddCase(Z_CND_SPLAT(weightedVal == 1));

        int weightedInitVal = zen::random::WeightedChoice({10, 20, 30}, {0, 0, 1});
        test.AddCase(Z_CND_SPLAT(weightedInitVal == 30));
    }

} // namespace example
