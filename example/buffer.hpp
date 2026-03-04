#pragma once

#include "zbuffer.hpp"
#include "ztest.hpp"
#include "zmacros.hpp"

#include <cassert>

namespace example
{
    struct TestData { float fVal; int iVal; };

    inline void BufferInsertion() noexcept
    {
        zutil::FastAccessBuffer<TestData> testBuffer {8};
        size_t dataID1 = testBuffer.Insert(TestData{1.0, 1});
        size_t dataID2 = testBuffer.Insert(TestData{2.0, 2});

        zutil::Test(Z_CND_SPLAT(testBuffer.At(dataID1).iVal == 1));
        zutil::Test(Z_CND_SPLAT(testBuffer.At(dataID2).iVal == 2));
    }

    inline void BufferRemoveing() noexcept
    {
        zutil::FastAccessBuffer<TestData> testBuffer {8};
        size_t dataID1 = testBuffer.Insert(TestData{1.0, 1});
        size_t dataID2 = testBuffer.Insert(TestData{2.0, 2});

        zutil::Test(Z_CND_SPLAT(testBuffer.Size() == 2));
        testBuffer.Remove(dataID1);
        zutil::Test(Z_CND_SPLAT(testBuffer.Size() == 1));
    }

    inline void BufferStressTest() noexcept
    {
        zutil::FastAccessBuffer<TestData> testBuffer {32};
        std::vector<size_t> indexes;
        indexes.reserve(32);

        for (int i = 0; i < 32; i ++)
            indexes[i] = testBuffer.Insert(TestData{static_cast<float>(i), i});

        for (int i = 0; i < 32; i ++)
            zutil::Test(Z_CND_SPLAT(testBuffer.At(indexes[i]).iVal == i));
    }

} // namespace example
