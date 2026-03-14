#pragma once

#include "angle.hpp"

#include <cmath>

namespace zen
{

    [[nodiscard]] inline f32 Sin(Angle angle) noexcept { return angle.Sin(); }
    [[nodiscard]] inline f32 Cos(Angle angle) noexcept { return angle.Cos(); }
    [[nodiscard]] inline f32 Tan(Angle angle) noexcept { return angle.Tan(); }

    [[nodiscard]] inline Angle ArcSin(f32 value) noexcept { return Angle::FromRadians(std::asin(value)); }
    [[nodiscard]] inline Angle ArcCos(f32 value) noexcept { return Angle::FromRadians(std::acos(value)); }
    [[nodiscard]] inline Angle ArcTan(f32 value) noexcept { return Angle::FromRadians(std::atan(value)); }

} // namespace zen
