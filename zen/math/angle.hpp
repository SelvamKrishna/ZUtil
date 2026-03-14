#pragma once

#include "../core/_export.hpp"
#include "../core/types.hpp"

namespace zen
{

    struct ZEN_API Angle
    {
    private:
        f32 _angleValue = 0.0f; // stored in radians

        constexpr Angle(f32 radians) : _angleValue {radians} {}

    public:
        [[nodiscard]] static constexpr Angle FromRadians(f32 radians);
        [[nodiscard]] static constexpr Angle FromDegrees(f32 degrees);

        [[nodiscard]] constexpr f32 AsRadians() const;
        [[nodiscard]] constexpr f32 AsDegrees() const;

        [[nodiscard]] Angle Normalized() const;

        [[nodiscard]] f32 Sin() noexcept;
        [[nodiscard]] f32 Cos() noexcept;
        [[nodiscard]] f32 Tan() noexcept;

        Angle operator + (Angle other) const;
        Angle operator - (Angle other) const;
        Angle operator * (f32 scalar) const;
        Angle operator / (f32 scalar) const;

        Angle& operator += (Angle other);
        Angle& operator -= (Angle other);

        bool operator == (Angle other) const;
        bool operator != (Angle other) const;
    };

} // namespace zen
