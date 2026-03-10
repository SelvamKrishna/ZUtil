#ifndef ZEN_BUILD
#define ZEN_BUILD
#endif

#include "random.hpp"

namespace zen::random
{

    inline std::mt19937 _randomEngine = {};

    std::mt19937& GetEngine() noexcept { return _randomEngine; }

    void SetSeed(u32 value) { _randomEngine.seed(value); }
    void SetTimeBasedSeed() { _randomEngine.seed(std::random_device{}()); }

    i16 RangeI16(i16 min, i16 max) { return Range<i16>(min, max); }
    i32 RangeI32(i32 min, i32 max) { return Range<i32>(min, max); }
    i64 RangeI64(i64 min, i64 max) { return Range<i64>(min, max); }

    u16 RangeU16(u16 min, u16 max) { return Range<u16>(min, max); }
    u32 RangeU32(u32 min, u32 max) { return Range<u32>(min, max); }
    u64 RangeU64(u64 min, u64 max) { return Range<u64>(min, max); }

    usize Index(usize size)
    {
        if (size == 0) throw std::invalid_argument {"Provided size must be greater than 0."};
        if (size == 1) return 0;
        return RangeU64(0, size - 1);
    }

    f32 RangeF32(f32 min, f32 max) { return Range<f32>(min, max); }
    f64 RangeF64(f64 min, f64 max) { return Range<f64>(min, max); }

    f32 UnitF32() { return RangeF32(0.0F, 1.0F); }
    f64 UnitF64() { return RangeF64(0.0 , 1.0 ); }

    f32 NormalF32(f32 mean, f32 standardDeviation) { return std::normal_distribution<f32>{mean, standardDeviation}(GetEngine()); }
    f64 NormalF64(f64 mean, f64 standardDeviation) { return std::normal_distribution<f64>{mean, standardDeviation}(GetEngine()); }

    bool Boolean() { return Range<u8>(0, 1); }
    bool Chance(f32 probability) { return RangeF32(0.0f, 1.0f) <= probability; }

    i32 SignI32() { return Boolean() ? 1 : -1; }
    f32 SignF32() { return Boolean() ? 1.0f : -1.0F; }

} // namespace zen::random
