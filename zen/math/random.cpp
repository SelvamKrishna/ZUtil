#ifndef ZEN_BUILD
#define ZEN_BUILD
#endif

#include "random.hpp"

namespace zen::random {

    inline std::mt19937 _randomEngine { GenerateSeed() };

    [[nodiscard]] std::mt19937& GetEngine() noexcept { return _randomEngine; }

    [[nodiscard]] core::u32 GenerateSeed() { return std::random_device{}(); }
    void SetSeed(core::u32 value) { _randomEngine.seed(value); }

    [[nodiscard]] core::i32 RangeI32(core::i32 min, core::i32 max) { return UniformDistribution<core::i32>(min, max); }
    [[nodiscard]] core::i64 RangeI64(core::i64 min, core::i64 max) { return UniformDistribution<core::i64>(min, max); }

    [[nodiscard]] core::u32 RangeU32(core::u32 min, core::u32 max) { return UniformDistribution<core::u32>(min, max); }
    [[nodiscard]] core::u64 RangeU64(core::u64 min, core::u64 max) { return UniformDistribution<core::u64>(min, max); }

    [[nodiscard]] core::f32 RangeF32(core::f32 min, core::f32 max) { return UniformDistribution<core::f32>(min, max); }
    [[nodiscard]] core::f64 RangeF64(core::f64 min, core::f64 max) { return UniformDistribution<core::f64>(min, max); }

    [[nodiscard]] core::f32 UnitF32() { return RangeF32(0.0F, 1.0F); }
    [[nodiscard]] core::f64 UnitF64() { return RangeF64(0.0 , 1.0 ); }

    [[nodiscard]] core::f32 NormalF32(core::f32 mean, core::f32 standardDeviation)
    {
        return NormalDistribution(mean, standardDeviation);
    }

    [[nodiscard]] core::f64 NormalF64(core::f64 mean, core::f64 standardDeviation)
    {
        return NormalDistribution(mean, standardDeviation);
    }

    [[nodiscard]] core::i32 SignI32() { return Boolean() ? 1 : -1; }
    [[nodiscard]] core::f32 SignF32() { return Boolean() ? 1.0f : -1.0F; }

    [[nodiscard]] core::usize Index(core::usize size)
    {
        if (size == 0) throw std::invalid_argument {"Provided size must be greater than 0."};
        if (size == 1) return 0;
        return RangeU64(0, size - 1);
    }

    [[nodiscard]] bool Boolean()                     { return UniformDistribution<core::u8>(0, 1); }
    [[nodiscard]] bool Chance(core::f32 probability) { return RangeF32(0.0f, 1.0f) <= probability; }

} // namespace zen::random
