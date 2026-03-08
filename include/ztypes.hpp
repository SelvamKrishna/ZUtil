#pragma once

#include <cstdint>
#include <cstddef>
#include <limits>

// ============================================================
// Primitive Types
// ============================================================

using i8  = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;

using u8  = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

static_assert(sizeof(i8)  == 1);
static_assert(sizeof(i16) == 2);
static_assert(sizeof(i32) == 4);
static_assert(sizeof(i64) == 8);

using f32 = float;
using f64 = double;

using usize = std::size_t;
using isize = std::ptrdiff_t;

using uptr = std::uintptr_t;
using iptr = std::intptr_t;

using byte = std::byte;

using char8  = char;
using char16 = char16_t;
using char32 = char32_t;
using wchar  = wchar_t;

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

inline constexpr f32 F32_MIN = std::numeric_limits<f32>::lowest();
inline constexpr f32 F32_MAX = std::numeric_limits<f32>::max();

inline constexpr f64 F64_MIN = std::numeric_limits<f64>::lowest();
inline constexpr f64 F64_MAX = std::numeric_limits<f64>::max();

inline constexpr f32 F32_EPSILON = std::numeric_limits<f32>::epsilon();
inline constexpr f64 F64_EPSILON = std::numeric_limits<f64>::epsilon();

inline constexpr f32 F32_INF = std::numeric_limits<f32>::infinity();
inline constexpr f64 F64_INF = std::numeric_limits<f64>::infinity();
