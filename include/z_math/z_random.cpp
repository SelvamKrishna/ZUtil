#include "z_random.hpp"

namespace zen
{
    std::mt19937 Random::_randomEngine = {};

    void Random::SetSeed(u32 value) { Random::_randomEngine.seed(value); }
    void Random::SetTimeBasedSeed() { Random::_randomEngine.seed(std::random_device{}()); }

    i16 Random::RangeI16(i16 min, i16 max)
    {
        std::uniform_int_distribution<i16> distribution {min, max};
        return distribution(Random::_randomEngine);
    }

    i32 Random::RangeI32(i32 min, i32 max)
    {
        std::uniform_int_distribution<i32> distribution {min, max};
        return distribution(Random::_randomEngine);
    }

    i64 Random::RangeI64(i64 min, i64 max)
    {
        std::uniform_int_distribution<i64> distribution {min, max};
        return distribution(Random::_randomEngine);
    }

    u16 Random::RangeU16(u16 min, u16 max)
    {
        std::uniform_int_distribution<u16> distribution {min, max};
        return distribution(Random::_randomEngine);
    }

    u32 Random::RangeU32(u32 min, u32 max)
    {
        std::uniform_int_distribution<u32> distribution {min, max};
        return distribution(Random::_randomEngine);
    }

    u64 Random::RangeU64(u64 min, u64 max)
    {
        std::uniform_int_distribution<u64> distribution {min, max};
        return distribution(Random::_randomEngine);
    }

    f32 Random::RangeF32(f32 min, f32 max)
    {
        std::uniform_real_distribution<f32> distribution {min, max};
        return distribution(Random::_randomEngine);
    }

    f64 Random::RangeF64(f64 min, f64 max)
    {
        std::uniform_real_distribution<f64> distribution {min, max};
        return distribution(Random::_randomEngine);
    }

    bool Random::Boolean() { return Random::RangeI32(0, 1) ? true : false; }
    bool Random::Chance(f32 probability) { return Random::RangeF32(0.0f, 1.0f) <= probability; }

    i32 Random::Sign() { return Random::Boolean() ? 1 : -1; }

} // namespace zen
