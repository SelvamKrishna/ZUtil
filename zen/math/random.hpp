#pragma once

#include "../core/_export.hpp"
#include "../core/types.hpp"
#include "constants.hpp"

#include <algorithm>
#include <random>
#include <type_traits>

namespace zen::random
{
    [[nodiscard]] ZEN_API std::mt19937& GetEngine() noexcept;

    ZEN_API void SetSeed(u32 value);
    ZEN_API void SetTimeBasedSeed();

    template <typename NumericT>
        requires std::is_integral_v<NumericT> || std::is_floating_point_v<NumericT>
    [[nodiscard]] NumericT Range(NumericT min, NumericT max)
    {
        if (min > max) std::swap(min, max);

        auto& engine = GetEngine();

        if constexpr (std::is_integral_v<NumericT>)
            return std::uniform_int_distribution<NumericT>{min, max}(engine);

        else
            return std::uniform_real_distribution<NumericT>{min, max}(engine);
    }

    [[nodiscard]] ZEN_API i16 RangeI16(i16 min = I16_MIN, i16 max = I16_MAX);
    [[nodiscard]] ZEN_API i32 RangeI32(i32 min = I32_MIN, i32 max = I32_MAX);
    [[nodiscard]] ZEN_API i64 RangeI64(i64 min = I64_MIN, i64 max = I64_MAX);

    [[nodiscard]] ZEN_API u16 RangeU16(u16 min = 0, u16 max = U16_MAX);
    [[nodiscard]] ZEN_API u32 RangeU32(u32 min = 0, u32 max = U32_MAX);
    [[nodiscard]] ZEN_API u64 RangeU64(u64 min = 0, u64 max = U64_MAX);

    [[nodiscard]] ZEN_API usize Index(usize size);

    [[nodiscard]] ZEN_API f32 RangeF32(f32 min = F32_MIN, f32 max = F32_MAX);
    [[nodiscard]] ZEN_API f64 RangeF64(f64 min = F64_MIN, f64 max = F64_MAX);

    [[nodiscard]] ZEN_API f32 UnitF32();
    [[nodiscard]] ZEN_API f64 UnitF64();

    [[nodiscard]] ZEN_API f32 NormalF32(f32 mean, f32 standardDeviation);
    [[nodiscard]] ZEN_API f64 NormalF64(f64 mean, f64 standardDeviation);

    [[nodiscard]] ZEN_API bool Boolean();
    [[nodiscard]] ZEN_API bool Chance(f32 probability);

    [[nodiscard]] ZEN_API i32 SignI32();
    [[nodiscard]] ZEN_API f32 SignF32();

    template <typename Container>
    [[nodiscard]] auto& Choice(Container& container) { return container[Index(container.size())]; }

    template <typename Container>
    [[nodiscard]] const auto& Choice(const Container& container) { return container[Index(container.size())]; }

    template <typename Iterator>
    void Shuffle(Iterator begin, Iterator end) { std::shuffle(begin, end, GetEngine()); }

} // namespace zen::random
