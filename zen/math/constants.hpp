#pragma once

#include "../core/types.hpp"

#include <limits>
#include <numbers>
#include <cmath>

namespace zen::constants {

    // ============================================================
    // Integer Limits
    // ============================================================
    inline constexpr core::i8  I8_MIN  = std::numeric_limits<core::i8>::min();
    inline constexpr core::i8  I8_MAX  = std::numeric_limits<core::i8>::max();
    inline constexpr core::i16 I16_MIN = std::numeric_limits<core::i16>::min();
    inline constexpr core::i16 I16_MAX = std::numeric_limits<core::i16>::max();
    inline constexpr core::i32 I32_MIN = std::numeric_limits<core::i32>::min();
    inline constexpr core::i32 I32_MAX = std::numeric_limits<core::i32>::max();
    inline constexpr core::i64 I64_MIN = std::numeric_limits<core::i64>::min();
    inline constexpr core::i64 I64_MAX = std::numeric_limits<core::i64>::max();

    inline constexpr core::u8  U8_MAX  = std::numeric_limits<core::u8>::max();
    inline constexpr core::u16 U16_MAX = std::numeric_limits<core::u16>::max();
    inline constexpr core::u32 U32_MAX = std::numeric_limits<core::u32>::max();
    inline constexpr core::u64 U64_MAX = std::numeric_limits<core::u64>::max();

    // ============================================================
    // Floating Point Limits
    // ============================================================
    inline constexpr core::f32 F32_MIN     = std::numeric_limits<core::f32>::min();
    inline constexpr core::f64 F64_MIN     = std::numeric_limits<core::f64>::min();
    inline constexpr core::f32 F32_LOWEST  = std::numeric_limits<core::f32>::lowest();
    inline constexpr core::f64 F64_LOWEST  = std::numeric_limits<core::f64>::lowest();
    inline constexpr core::f32 F32_MAX     = std::numeric_limits<core::f32>::max();
    inline constexpr core::f64 F64_MAX     = std::numeric_limits<core::f64>::max();
    inline constexpr core::f32 F32_EPSILON = std::numeric_limits<core::f32>::epsilon();
    inline constexpr core::f64 F64_EPSILON = std::numeric_limits<core::f64>::epsilon();

    inline constexpr core::f32 F32_INFINITY     = std::numeric_limits<core::f32>::infinity();
    inline constexpr core::f64 F64_INFINITY     = std::numeric_limits<core::f64>::infinity();
    inline constexpr core::f32 F32_NEG_INFINITY = -F32_INFINITY;
    inline constexpr core::f64 F64_NEG_INFINITY = -F64_INFINITY;

    // ============================================================
    // Mathematical Constants
    // ============================================================
    inline constexpr core::f32 F32_PI       = static_cast<core::f32>(std::numbers::pi);
    inline constexpr core::f64 F64_PI       = static_cast<core::f64>(std::numbers::pi);
    inline constexpr core::f32 F32_TWO_PI   = static_cast<core::f32>(2 * std::numbers::pi);
    inline constexpr core::f64 F64_TWO_PI   = static_cast<core::f64>(2 * std::numbers::pi);
    inline constexpr core::f32 F32_HALF_PI  = static_cast<core::f32>(std::numbers::pi / 2);
    inline constexpr core::f64 F64_HALF_PI  = static_cast<core::f64>(std::numbers::pi / 2);
    inline constexpr core::f32 F32_INV_PI   = static_cast<core::f32>(1.0 / std::numbers::pi);
    inline constexpr core::f64 F64_INV_PI   = static_cast<core::f64>(1.0 / std::numbers::pi);

    inline constexpr core::f32 F32_GOLDEN_RATIO = 1.61803398875f;
    inline constexpr core::f64 F64_GOLDEN_RATIO = 1.61803398875;

} // namespace zen::constants

namespace zen::math {

    [[nodiscard]] inline bool CompareF32Eq(core::f32 lhs, core::f32 rhs, core::f32 epsilon = constants::F32_EPSILON) noexcept
    {
        return std::abs(rhs - lhs) < epsilon;
    }

    [[nodiscard]] inline bool CompareF64Eq(core::f64 lhs, core::f64 rhs, core::f64 epsilon = constants::F64_EPSILON) noexcept
    {
        return std::abs(rhs - lhs) < epsilon;
    }

} // namespace zen::math
