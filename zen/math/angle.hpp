#pragma once

#include "../core/_export.hpp"
#include "../core/types.hpp"

namespace zen::math {

    [[nodiscard]] constexpr core::f32 DegreesToRadians(core::f32 degrees) noexcept;
    [[nodiscard]] constexpr core::f32 RadiansToDegrees(core::f32 radians) noexcept;

    struct ZEN_API Angle
    {
    private:
        core::f32 _radians = 0.0f;

        constexpr Angle(core::f32 radians) : _radians {radians} {}

    public:
        [[nodiscard]] static constexpr Angle FromRadians(core::f32 radians);
        [[nodiscard]] static constexpr Angle FromDegrees(core::f32 degrees);

        [[nodiscard]] constexpr core::f32 AsRadians() const;
        [[nodiscard]] constexpr core::f32 AsDegrees() const;

        [[nodiscard]] Angle Normalized() const;

        [[nodiscard]] core::f32 Sin() noexcept;
        [[nodiscard]] core::f32 Cos() noexcept;
        [[nodiscard]] core::f32 Tan() noexcept;

        Angle operator + (Angle other) const;
        Angle operator - (Angle other) const;
        Angle operator * (core::f32 scalar) const;
        Angle operator / (core::f32 scalar) const;

        Angle& operator += (Angle other);
        Angle& operator -= (Angle other);

        bool operator == (Angle other) const;
        bool operator != (Angle other) const;
    };

} // namespace zen::math
