#pragma once

#include "z_types.hpp"

#include <random>

namespace zen
{

    struct Random
    {
    private:
        static std::mt19937 _randomEngine;

    public:
        static void SetSeed(u32 value);
        static void SetTimeBasedSeed();

        static i16 RangeI16(i16 min, i16 max);
        static i32 RangeI32(i32 min, i32 max);
        static i64 RangeI64(i64 min, i64 max);

        static u16 RangeU16(u16 min, u16 max);
        static u32 RangeU32(u32 min, u32 max);
        static u64 RangeU64(u64 min, u64 max);

        static f32 RangeF32(f32 min, f32 max);
        static f64 RangeF64(f64 min, f64 max);

        static bool Boolean();
        static bool Chance(f32 probability);

        static i32 Sign();

    };

} // namespace zen
