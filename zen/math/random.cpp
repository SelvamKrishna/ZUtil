#ifndef ZEN_BUILD
#define ZEN_BUILD
#endif

#include "random.hpp"

namespace zen::random
{

    inline std::mt19937 _randomEngine = {};

    [[nodiscard]] std::mt19937& GetEngine() noexcept { return _randomEngine; }

    [[nodiscard]] u64 GenerateSeed() { return std::random_device{}(); }
    void SetSeed(u32 value) { _randomEngine.seed(value); }

    [[nodiscard]] i32 RangeI32(i32 min, i32 max) { return UniformDistribution<i32>(min, max); }
    [[nodiscard]] i64 RangeI64(i64 min, i64 max) { return UniformDistribution<i64>(min, max); }

    [[nodiscard]] u32 RangeU32(u32 min, u32 max) { return UniformDistribution<u32>(min, max); }
    [[nodiscard]] u64 RangeU64(u64 min, u64 max) { return UniformDistribution<u64>(min, max); }

    [[nodiscard]] f32 RangeF32(f32 min, f32 max) { return UniformDistribution<f32>(min, max); }
    [[nodiscard]] f64 RangeF64(f64 min, f64 max) { return UniformDistribution<f64>(min, max); }

    [[nodiscard]] f32 UnitF32() { return RangeF32(0.0F, 1.0F); }
    [[nodiscard]] f64 UnitF64() { return RangeF64(0.0 , 1.0 ); }

    [[nodiscard]] f32 NormalF32(f32 mean, f32 standardDeviation)
    {
        return NormalDistribution(mean, standardDeviation);
    }

    [[nodiscard]] f64 NormalF64(f64 mean, f64 standardDeviation)
    {
        return NormalDistribution(mean, standardDeviation);
    }

    [[nodiscard]] i32 SignI32() { return Boolean() ? 1 : -1; }
    [[nodiscard]] f32 SignF32() { return Boolean() ? 1.0f : -1.0F; }

    [[nodiscard]] usize Index(usize size)
    {
        if (size == 0) throw std::invalid_argument {"Provided size must be greater than 0."};
        if (size == 1) return 0;
        return RangeU64(0, size - 1);
    }

    [[nodiscard]] bool Boolean()               { return UniformDistribution<u8>(0, 1); }
    [[nodiscard]] bool Chance(f32 probability) { return RangeF32(0.0f, 1.0f) <= probability; }

} // namespace zen::random
