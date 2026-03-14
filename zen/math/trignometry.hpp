#pragma once

#include "angle.hpp"

#include <cmath>

namespace zen::math {

    [[nodiscard]] inline core::f32 Sin(Angle angle) noexcept { return angle.Sin(); }
    [[nodiscard]] inline core::f32 Cos(Angle angle) noexcept { return angle.Cos(); }
    [[nodiscard]] inline core::f32 Tan(Angle angle) noexcept { return angle.Tan(); }

    [[nodiscard]] inline Angle ArcSin(core::f32 value) noexcept { return Angle::FromRadians(std::asin(value)); }
    [[nodiscard]] inline Angle ArcCos(core::f32 value) noexcept { return Angle::FromRadians(std::acos(value)); }
    [[nodiscard]] inline Angle ArcTan(core::f32 value) noexcept { return Angle::FromRadians(std::atan(value)); }

} // namespace zen::math
