#ifndef ZEN_BUILD
#define ZEN_BUILD
#endif

#include "angle.hpp"
#include "constants.hpp"

#include <cmath>

namespace zen
{

    [[nodiscard]] constexpr Angle Angle::FromRadians(float radians) { return Angle {radians}; }
    [[nodiscard]] constexpr Angle Angle::FromDegrees(float degrees) { return Angle {degrees * (F32_PI / 180.0f)}; }

    [[nodiscard]] constexpr f32 Angle::AsRadians() const { return this->_angleValue; }
    [[nodiscard]] constexpr f32 Angle::AsDegrees() const { return this->_angleValue * (180.0f / F32_PI); }

    [[nodiscard]] Angle Angle::Normalized() const
    {
        f32 normalRadian = std::fmod(this->AsRadians(), F32_TWO_PI);
        if (normalRadian < 0.0f) normalRadian += F32_TWO_PI;
        return Angle {normalRadian};
    }

    Angle Angle::operator + (Angle other)  const { return Angle {this->_angleValue + other._angleValue}; }
    Angle Angle::operator - (Angle other)  const { return Angle {this->_angleValue - other._angleValue}; }
    Angle Angle::operator * (float scalar) const { return Angle {this->_angleValue * scalar}; }
    Angle Angle::operator / (float scalar) const { return Angle {this->_angleValue / scalar}; }

    Angle& Angle::operator += (Angle other) { this->_angleValue += other._angleValue; return *this; }
    Angle& Angle::operator -= (Angle other) { this->_angleValue -= other._angleValue; return *this; }

    bool Angle::operator == (Angle other) const { return this->_angleValue == other._angleValue; }
    bool Angle::operator != (Angle other) const { return this->_angleValue != other._angleValue; }

} // namespace zen
