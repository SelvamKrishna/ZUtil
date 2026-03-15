#pragma once

#include "../core/types.hpp"

#include <limits>
#include <numbers>

namespace zen::constants {

    // ============================================================
    // Integer Limits
    // ============================================================
    inline constexpr i8  I8_MIN  = std::numeric_limits<i8>::min();
    inline constexpr i8  I8_MAX  = std::numeric_limits<i8>::max();
    inline constexpr i16 I16_MIN = std::numeric_limits<i16>::min();
    inline constexpr i16 I16_MAX = std::numeric_limits<i16>::max();
    inline constexpr i32 I32_MIN = std::numeric_limits<i32>::min();
    inline constexpr i32 I32_MAX = std::numeric_limits<i32>::max();
    inline constexpr i64 I64_MIN = std::numeric_limits<i64>::min();
    inline constexpr i64 I64_MAX = std::numeric_limits<i64>::max();

    inline constexpr u8  U8_MAX  = std::numeric_limits<u8>::max();
    inline constexpr u16 U16_MAX = std::numeric_limits<u16>::max();
    inline constexpr u32 U32_MAX = std::numeric_limits<u32>::max();
    inline constexpr u64 U64_MAX = std::numeric_limits<u64>::max();

    // ============================================================
    // Floating Point Limits
    // ============================================================
    inline constexpr f32 F32_MIN     = std::numeric_limits<f32>::min();
    inline constexpr f64 F64_MIN     = std::numeric_limits<f64>::min();
    inline constexpr f32 F32_LOWEST  = std::numeric_limits<f32>::lowest();
    inline constexpr f64 F64_LOWEST  = std::numeric_limits<f64>::lowest();
    inline constexpr f32 F32_MAX     = std::numeric_limits<f32>::max();
    inline constexpr f64 F64_MAX     = std::numeric_limits<f64>::max();

    inline constexpr f32 F32_EPSILON = std::numeric_limits<f32>::epsilon();
    inline constexpr f64 F64_EPSILON = std::numeric_limits<f64>::epsilon();
    inline constexpr f32 F32_COMPARE_EPSILON = 1e-4f;
    inline constexpr f64 F64_COMPARE_EPSILON = 1e-4f;
    inline constexpr f32 F32_NORMAL_EPSILON  = 1e-8f;
    inline constexpr f64 F64_NORMAL_EPSILON  = 1e-8f;

    inline constexpr f32 F32_INFINITY     = std::numeric_limits<f32>::infinity();
    inline constexpr f64 F64_INFINITY     = std::numeric_limits<f64>::infinity();
    inline constexpr f32 F32_NEG_INFINITY = -F32_INFINITY;
    inline constexpr f64 F64_NEG_INFINITY = -F64_INFINITY;

    // ============================================================
    // Mathematical Constants
    // ============================================================
    inline constexpr f32 F32_PI       = static_cast<f32>(std::numbers::pi);
    inline constexpr f64 F64_PI       = static_cast<f64>(std::numbers::pi);
    inline constexpr f32 F32_TWO_PI   = static_cast<f32>(2 * std::numbers::pi);
    inline constexpr f64 F64_TWO_PI   = static_cast<f64>(2 * std::numbers::pi);
    inline constexpr f32 F32_TAU      = F32_TWO_PI;
    inline constexpr f64 F64_TAU      = F64_TWO_PI;
    inline constexpr f32 F32_HALF_PI  = static_cast<f32>(std::numbers::pi / 2);
    inline constexpr f64 F64_HALF_PI  = static_cast<f64>(std::numbers::pi / 2);
    inline constexpr f32 F32_INV_PI   = static_cast<f32>(1.0 / std::numbers::pi);
    inline constexpr f64 F64_INV_PI   = static_cast<f64>(1.0 / std::numbers::pi);

    inline constexpr f32 F32_GOLDEN_RATIO = 1.61803398875f;
    inline constexpr f64 F64_GOLDEN_RATIO = 1.61803398875;

} // namespace zen::constants
