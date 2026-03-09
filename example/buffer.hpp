#pragma once

#include "z_container/z_fast_access_buffer.hpp"
#include "z_container/z_spares_set.hpp"
#include "z_container/z_double_buffer.hpp"

#include "z_test.hpp"
#include "z_macros.hpp"

#include <cassert>

namespace example
{
    struct TestData { float fVal; int iVal; };

    inline void FastAccessBuffer() noexcept
    {
        zen::TestSuite test {__PRETTY_FUNCTION__};

        zen::FastAccessBuffer<TestData> testBuffer {8};
        size_t dataID1 = testBuffer.Insert(TestData{1.0, 1});
        size_t dataID2 = testBuffer.Insert(TestData{2.0, 2});

        test.AddCase(Z_CND_SPLAT(testBuffer[dataID1].iVal == 1));
        test.AddCase(Z_CND_SPLAT(testBuffer[dataID2].iVal == 2));

        test.AddCase(Z_CND_SPLAT(testBuffer.Size() == 2));
        testBuffer.Remove(dataID1);
        test.AddCase(Z_CND_SPLAT(testBuffer.Size() == 1));
        testBuffer.Remove(dataID2);
        test.AddCase(Z_CND_SPLAT(testBuffer.Size() == 0));
    }

    inline void SparseSetInsertion() noexcept
    {
        zen::TestSuite test {__PRETTY_FUNCTION__};

        zen::SparseSet<TestData> testBuffer {8, 8};
        testBuffer.Insert(1, TestData{1.0, 1});
        testBuffer.Insert(2, TestData{2.0, 2});

        try {
            testBuffer.Insert(2, TestData{2.0, 2});
        } catch (std::invalid_argument err) {
            test.AddCase(true, err.what());
        }

        test.AddCase(Z_CND_SPLAT(testBuffer.Contains(2)));
        test.AddCase(Z_CND_SPLAT(!testBuffer.Contains(3)));
        test.AddCase(Z_CND_SPLAT(testBuffer.Size() == 2));

        testBuffer.Remove(1);
        testBuffer.Remove(2);

        try {
            testBuffer.Remove(3);
        } catch (std::invalid_argument err) {
            test.AddCase(true, err.what());
        }

        test.AddCase(Z_CND_SPLAT(!testBuffer.Contains(1)));
        test.AddCase(Z_CND_SPLAT(!testBuffer.Contains(2)));
        test.AddCase(Z_CND_SPLAT(testBuffer.Size() == 0));
    }

    inline void DoubleBuffer() noexcept
    {
        zen::TestSuite test {__PRETTY_FUNCTION__};
        zen::DoubleBuffer<TestData> testBuffer;

        test.AddCase(Z_CND_SPLAT(testBuffer.Read().fVal == 0.0));
        test.AddCase(Z_CND_SPLAT(testBuffer.Read().iVal == 0));

        testBuffer.Write().fVal = 1.0;
        testBuffer.Write().iVal = 1;

        testBuffer.Swap();

        testBuffer.Write().fVal = 2.0;
        testBuffer.Write().iVal = 2;

        test.AddCase(Z_CND_SPLAT(testBuffer.Read().fVal == 1.0));
        test.AddCase(Z_CND_SPLAT(testBuffer.Read().iVal == 1));

        testBuffer.Swap();

        test.AddCase(Z_CND_SPLAT(testBuffer.Read().fVal == 2.0));
        test.AddCase(Z_CND_SPLAT(testBuffer.Read().iVal == 2));
    }

} // namespace example
