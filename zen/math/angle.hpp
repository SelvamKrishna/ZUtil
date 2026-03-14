#pragma once

#include "../core/_export.hpp"
#include "../core/types.hpp"

namespace zen::math {

    struct ZEN_API Angle
    {
    private:
        core::f32 _angleValue = 0.0f; // stored in radians

        constexpr Angle(core::f32 radians) : _angleValue {radians} {}

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
