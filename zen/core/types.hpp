#pragma once

#include <cstdint>
#include <cstddef>

namespace zen::core {

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

} // namespace zen::core
