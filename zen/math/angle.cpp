#ifndef ZEN_BUILD
#define ZEN_BUILD
#endif

#include "angle.hpp"
#include "constants.hpp"

#include <cmath>

namespace zen::math {

    [[nodiscard]] constexpr core::f32 DegreesToRadians(core::f32 degrees) noexcept
    {
        return degrees * constants::F32_PI / 180.0F;
    }

    [[nodiscard]] constexpr core::f32 RadiansToDegrees(core::f32 radians) noexcept
    {
        return radians * 180.0F / constants::F32_PI;
    }

    [[nodiscard]] constexpr Angle Angle::FromRadians(core::f32 radians) { return Angle {radians}; }
    [[nodiscard]] constexpr Angle Angle::FromDegrees(core::f32 degrees) { return Angle {DegreesToRadians(degrees)}; }

    [[nodiscard]] constexpr core::f32 Angle::AsRadians() const { return this->_radians; }
    [[nodiscard]] constexpr core::f32 Angle::AsDegrees() const { return RadiansToDegrees(this->_radians); }

    [[nodiscard]] Angle Angle::Normalized() const
    {
        core::f32 normalRadian = std::fmod(this->AsRadians(), constants::F32_TWO_PI);
        if (normalRadian < 0.0f) normalRadian += constants::F32_TWO_PI;
        return Angle {normalRadian};
    }

    [[nodiscard]] core::f32 Angle::Sin() noexcept { return std::sin(this->AsRadians()); }
    [[nodiscard]] core::f32 Angle::Cos() noexcept { return std::cos(this->AsRadians()); }
    [[nodiscard]] core::f32 Angle::Tan() noexcept { return std::tan(this->AsRadians()); }

    [[nodiscard]] Angle Angle::operator + (Angle other) const { return Angle {this->AsRadians() + other.AsRadians()}; }
    [[nodiscard]] Angle Angle::operator - (Angle other) const { return Angle {this->AsRadians() - other.AsRadians()}; }
    [[nodiscard]] Angle Angle::operator * (core::f32 scalar) const { return Angle {this->AsRadians() * scalar}; }
    [[nodiscard]] Angle Angle::operator / (core::f32 scalar) const { return Angle {this->AsRadians() / scalar}; }

    Angle& Angle::operator += (Angle other) { this->_radians += other.AsRadians(); return *this; }
    Angle& Angle::operator -= (Angle other) { this->_radians -= other.AsRadians(); return *this; }

    [[nodiscard]] bool Angle::operator == (Angle other) const { return  CompareF32Eq(this->AsRadians(), other.AsRadians()); }
    [[nodiscard]] bool Angle::operator != (Angle other) const { return !CompareF32Eq(this->AsRadians(), other.AsRadians()); }

    [[nodiscard]] bool Angle::operator < (Angle other) const { return this->Normalized().AsRadians() < other.Normalized().AsRadians(); }
    [[nodiscard]] bool Angle::operator > (Angle other) const { return this->Normalized().AsRadians() > other.Normalized().AsRadians(); }

    [[nodiscard]] bool Angle::operator <= (Angle other) const { return this->Normalized().AsRadians() <= other.Normalized().AsRadians(); }
    [[nodiscard]] bool Angle::operator >= (Angle other) const { return this->Normalized().AsRadians() >= other.Normalized().AsRadians(); }

} // namespace zen::math
