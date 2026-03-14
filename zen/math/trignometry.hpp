#pragma once

#include "angle.hpp"

#include <cmath>

namespace zen::math {

    /// @brief Computes the sine of the angle.
    [[nodiscard]] inline core::f32 Sin(Angle angle) noexcept { return angle.Sin(); }

    /// @brief Computes the cosine of the angle.
    [[nodiscard]] inline core::f32 Cos(Angle angle) noexcept { return angle.Cos(); }

    /// @brief Computes the tangent of the angle.
    [[nodiscard]] inline core::f32 Tan(Angle angle) noexcept { return angle.Tan(); }

    /// @brief Computes the angle using the sine value.
    [[nodiscard]] inline Angle ArcSin(core::f32 sinValue) noexcept { return Angle::FromRadians(std::asin(sinValue)); }

    /// @brief Computes the angle using the cosine value.
    [[nodiscard]] inline Angle ArcCos(core::f32 cosValue) noexcept { return Angle::FromRadians(std::acos(cosValue)); }

    /// @brief Computes the angle using the tangent value.
    [[nodiscard]] inline Angle ArcTan(core::f32 tanValue) noexcept { return Angle::FromRadians(std::atan(tanValue)); }

} // namespace zen::math
