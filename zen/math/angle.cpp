#ifndef ZEN_BUILD
#define ZEN_BUILD
#endif

#include "angle.hpp"
#include "constants.hpp"
#include "utils.hpp"

#include <cmath>

namespace zen::math {

    [[nodiscard]] Angle Angle::Normalized() const
    {
        return {
            this->_radians - constants::F32_TAU * std::floor(this->_radians / constants::F32_TAU)
        };
    }

    [[nodiscard]] f32 Angle::Sin() const noexcept { return std::sin(this->_radians); }
    [[nodiscard]] f32 Angle::Cos() const noexcept { return std::cos(this->_radians); }
    [[nodiscard]] f32 Angle::Tan() const noexcept { return std::tan(this->_radians); }

    [[nodiscard]] Angle Angle::operator + (Angle other) const { return {this->_radians + other._radians}; }
    [[nodiscard]] Angle Angle::operator - (Angle other) const { return {this->_radians - other._radians}; }
    [[nodiscard]] Angle Angle::operator * (f32 scalar)  const { return {this->_radians * scalar}; }
    [[nodiscard]] Angle Angle::operator / (f32 scalar)  const { return {this->_radians / scalar}; }

    Angle& Angle::operator += (Angle other) { this->_radians += other._radians; return *this; }
    Angle& Angle::operator -= (Angle other) { this->_radians -= other._radians; return *this; }

    [[nodiscard]] bool Angle::operator == (Angle other) const { return  NearlyEqual(this->_radians, other._radians); }
    [[nodiscard]] bool Angle::operator != (Angle other) const { return !NearlyEqual(this->_radians, other._radians); }

    [[nodiscard]] bool Angle::operator < (Angle other) const { return this->Normalized()._radians < other.Normalized()._radians; }
    [[nodiscard]] bool Angle::operator > (Angle other) const { return this->Normalized()._radians > other.Normalized()._radians; }

    [[nodiscard]] bool Angle::operator <= (Angle other) const { return this->Normalized()._radians <= other.Normalized()._radians; }
    [[nodiscard]] bool Angle::operator >= (Angle other) const { return this->Normalized()._radians >= other.Normalized()._radians; }

} // namespace zen::math
