#pragma once

#include "angle.hpp"
#include "vec2.hpp"

#include <cmath>

namespace zen::math {

    /// @brief Computes the sine of the angle.
    [[nodiscard]] inline f32 Sin(Angle angle) noexcept { return angle.Sin(); }

    /// @brief Computes the cosine of the angle.
    [[nodiscard]] inline f32 Cos(Angle angle) noexcept { return angle.Cos(); }

    /// @brief Computes the tangent of the angle.
    [[nodiscard]] inline f32 Tan(Angle angle) noexcept { return angle.Tan(); }

    /// @brief Computes the angle using the sine value.
    [[nodiscard]] inline Angle ArcSin(f32 sinValue) noexcept { return Angle::FromRadians(std::asin(sinValue)); }

    /// @brief Computes the angle using the cosine value.
    [[nodiscard]] inline Angle ArcCos(f32 cosValue) noexcept { return Angle::FromRadians(std::acos(cosValue)); }

    /// @brief Computes the angle using the tangent value.
    [[nodiscard]] inline Angle ArcTan(f32 tanValue) noexcept { return Angle::FromRadians(std::atan(tanValue)); }

    /// @brief Computes the angle using the point coordinates.
    [[nodiscard]] inline Angle ArcTan(Vec2f coordinate) noexcept { return coordinate.GetAngle(); }

} // namespace zen::math
