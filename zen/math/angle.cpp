#ifndef ZEN_BUILD
#define ZEN_BUILD
#endif

#include "angle.hpp"
#include "constants.hpp"

#include <cmath>

namespace zen::math {

    [[nodiscard]] constexpr Angle Angle::FromRadians(float radians) { return Angle {radians}; }
    [[nodiscard]] constexpr Angle Angle::FromDegrees(float degrees) { return Angle {degrees * (F32_PI / 180.0f)}; }

    [[nodiscard]] constexpr core::f32 Angle::AsRadians() const { return this->_angleValue; }
    [[nodiscard]] constexpr core::f32 Angle::AsDegrees() const { return this->_angleValue * (180.0f / F32_PI); }

    [[nodiscard]] Angle Angle::Normalized() const
    {
        core::f32 normalRadian = std::fmod(this->AsRadians(), F32_TWO_PI);
        if (normalRadian < 0.0f) normalRadian += F32_TWO_PI;
        return Angle {normalRadian};
    }

    [[nodiscard]] core::f32 Angle::Sin() noexcept { return std::sin(this->_angleValue); }
    [[nodiscard]] core::f32 Angle::Cos() noexcept { return std::cos(this->_angleValue); }
    [[nodiscard]] core::f32 Angle::Tan() noexcept { return std::tan(this->_angleValue); }

    Angle Angle::operator + (Angle other) const { return Angle {this->AsRadians() + other.AsRadians()}; }
    Angle Angle::operator - (Angle other) const { return Angle {this->AsRadians() - other.AsRadians()}; }
    Angle Angle::operator * (core::f32 scalar) const { return Angle {this->AsRadians() * scalar}; }
    Angle Angle::operator / (core::f32 scalar) const { return Angle {this->AsRadians() / scalar}; }

    Angle& Angle::operator += (Angle other) { this->_angleValue += other.AsRadians(); return *this; }
    Angle& Angle::operator -= (Angle other) { this->_angleValue -= other.AsRadians(); return *this; }

    bool Angle::operator == (Angle other) const { return this->AsRadians() == other.AsRadians(); }
    bool Angle::operator != (Angle other) const { return this->AsRadians() != other.AsRadians(); }

} // namespace zen::math
