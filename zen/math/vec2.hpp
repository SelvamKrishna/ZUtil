#pragma once

#include "angle.hpp"
#include "../core/types.hpp"

#include <algorithm>
#include <cmath>
#include <type_traits>

namespace zen::math {

    /// ---
    /// @brief 2-dimensional vector type.
    /// Represents a mathematical vector with `x` and `y` components.
    /// @tparam ValueT Arithmetic type used for vector components.
    /// ---
    template <typename ValueT>
        requires std::is_arithmetic_v<ValueT>
    struct Vec2 {
    public:
        ValueT x; ///< X component of the vector.
        ValueT y; ///< Y component of the vector.

        /// @brief Default constructor.
        constexpr Vec2() noexcept = default;

        /// @brief Constructs a vector with specified components.
        /// @param x X component.
        /// @param y Y component.
        constexpr Vec2(ValueT x, ValueT y) noexcept : x{x}, y{y} {}

        /// @brief Returns a zero vector.
        [[nodiscard]] static constexpr Vec2 Zero() noexcept
        {
            return {static_cast<ValueT>(0), static_cast<ValueT>(0)};
        }

        /// @brief Returns a vector with all components equal to 1.
        [[nodiscard]] static constexpr Vec2 One() noexcept
        {
            return {static_cast<ValueT>(1), static_cast<ValueT>(1)};
        }

        /// @brief Returns the unit vector pointing upward.
        [[nodiscard]] static constexpr Vec2 Up() noexcept
        {
            return {static_cast<ValueT>(0), static_cast<ValueT>(1)};
        }

        /// @brief Returns the unit vector pointing downward.
        [[nodiscard]] static constexpr Vec2 Down() noexcept
        {
            return {static_cast<ValueT>(0), static_cast<ValueT>(-1)};
        }

        /// @brief Returns the unit vector pointing left.
        [[nodiscard]] static constexpr Vec2 Left() noexcept
        {
            return {static_cast<ValueT>(-1), static_cast<ValueT>(0)};
        }

        /// @brief Returns the unit vector pointing right.
        [[nodiscard]] static constexpr Vec2 Right() noexcept
        {
            return {static_cast<ValueT>(1), static_cast<ValueT>(0)};
        }

        /// @brief Returns a vector where both components equal the specified value.
        /// @param value Value for both components.
        [[nodiscard]] static constexpr Vec2 Unit(ValueT value = static_cast<ValueT>(1)) noexcept
        {
            return {value, value};
        }

        /// @brief Returns a vector rotated 90 degrees counter-clockwise.
        [[nodiscard]] constexpr Vec2 Rotated90() const noexcept { return {-this->y, this->x}; }

        /// @brief Returns a vector rotated 270 degrees counter-clockwise.
        [[nodiscard]] constexpr Vec2 Rotated270() const noexcept { return {this->y, -this->x}; }

        /// @brief Rotates the vector by the specified angle.
        /// @param rotationAngle Angle of rotation.
        [[nodiscard]] Vec2 Rotated(Angle rotationAngle) const noexcept
        {
            const core::f32 SIN_VAL = rotationAngle.Sin();
            const core::f32 COS_VAL = rotationAngle.Cos();

            return {
                static_cast<ValueT>(x * COS_VAL - y * SIN_VAL),
                static_cast<ValueT>(x * SIN_VAL + y * COS_VAL)
            };
        }

        /// @brief Computes the dot product between two vectors.
        [[nodiscard]] constexpr ValueT Dot(const Vec2& other) const noexcept
        {
            return this->x * other.x + this->y * other.y;
        }

        /// @brief Computes the 2D cross product (scalar).
        [[nodiscard]] constexpr ValueT Cross(const Vec2& other) const noexcept
        {
            return this->x * other.y - this->y * other.x;
        }

        /// @brief Returns a perpendicular vector.
        [[nodiscard]] constexpr Vec2 Perpendicular() const noexcept { return {-this->y, this->x}; }

        /// @brief Computes the squared magnitude of the vector.
        [[nodiscard]] constexpr ValueT LengthSquared() const noexcept
        {
            return this->x * this->x + this->y * this->y;
        }

        /// @brief Computes the magnitude of the vector.
        [[nodiscard]] core::f32 Length() const noexcept
        {
            return std::hypot(static_cast<core::f32>(this->x), static_cast<core::f32>(this->y));
        }

        /// @brief Returns the reciprocal of the vector length.
        [[nodiscard]] core::f32 LengthInverse() const noexcept
        {
            core::f32 lengthSquared = static_cast<core::f32>(this->LengthSquared());
            if (lengthSquared == 0) return 0.0f;
            return 1.0f / std::sqrt(lengthSquared);
        }

        /// @brief Computes the squared distance between two vectors.
        [[nodiscard]] ValueT DistanceSquared(const Vec2& other) const noexcept
        {
            ValueT dx = this->x - other.x;
            ValueT dy = this->y - other.y;
            return dx * dx + dy * dy;
        }

        /// @brief Computes the distance between two vectors.
        [[nodiscard]] core::f32 Distance(const Vec2& other) const noexcept
        {
            return (*this - other).Length();
        }

        /// @brief Returns a normalized version of the vector.
        [[nodiscard]] Vec2 Normalized() const noexcept
        {
            const core::f32 MAGNITUDE = this->Length();
            if (MAGNITUDE == 0) return Vec2::Zero();
            return *this / static_cast<ValueT>(MAGNITUDE);
        }

        /// @brief Normalizes the vector in-place.
        void Normalize() noexcept { *this = this->Normalized(); }

        /// @brief Computes the angle between two vectors.
        [[nodiscard]] Angle AngleBetween(const Vec2& other) const noexcept
        {
            const core::f32 COMBINED_MAGNITUDE = this->Length() * other.Length();
            if (COMBINED_MAGNITUDE == 0) return Angle::FromRadians(0);

            const core::f32 COS_VAL = static_cast<core::f32>(this->Dot(other)) / COMBINED_MAGNITUDE;
            return Angle::FromRadians(std::acos(std::clamp(COS_VAL, -1.0f, 1.0f)));
        }

        /// @brief Computes the signed angle between two vectors.
        [[nodiscard]] Angle SignedAngle(const Vec2& other) const noexcept
        {
            return Angle::FromRadians(
                std::atan2(
                    static_cast<core::f32>(this->Cross(other)),
                    static_cast<core::f32>(this->Dot(other))
                )
            );
        }

        /// @brief Returns the polar angle of the vector.
        [[nodiscard]] Angle GetAngle() const noexcept
        {
            return Angle::FromRadians(
                std::atan2(static_cast<core::f32>(this->y), static_cast<core::f32>(this->x))
            );
        }

        /// @brief Reflects the vector across a normal.
        [[nodiscard]] Vec2 Reflect(const Vec2& normal) const noexcept
        {
            return *this - normal * (static_cast<ValueT>(2) * this->Dot(normal));
        }

        /// @brief Projects the vector onto another vector.
        [[nodiscard]] Vec2 Project(const Vec2& other) const noexcept
        {
            ValueT denom = other.LengthSquared();
            if (denom == 0) return Vec2::Zero();
            return other * (this->Dot(other) / denom);
        }

        /// @brief Clamps the vector magnitude to a maximum length.
        [[nodiscard]] Vec2 ClampLength(ValueT maxLength) const noexcept
        {
            ValueT lengthSquared = this->LengthSquared();
            ValueT maxLengthSquared = maxLength * maxLength;
            return (lengthSquared > maxLengthSquared) ? this->Normalized() * maxLength : *this;
        }

        /// @brief Linearly interpolates between two vectors.
        [[nodiscard]] static constexpr Vec2 Lerp(const Vec2& start, const Vec2& end, ValueT travel) noexcept
        {
            return start + (end - start) * travel;
        }

        /// @brief Creates a unit vector from an angle.
        [[nodiscard]] static Vec2 FromAngle(const Angle& angle) noexcept
        {
            return {
                static_cast<ValueT>(angle.Cos()),
                static_cast<ValueT>(angle.Sin())
            };
        }

        [[nodiscard]] constexpr Vec2 operator - () const noexcept { return {-this->x, -this->y}; }

        [[nodiscard]] constexpr Vec2 operator + (const Vec2& other) const noexcept { return {this->x + other.x, this->y + other.y}; }
        [[nodiscard]] constexpr Vec2 operator - (const Vec2& other) const noexcept { return {this->x - other.x, this->y - other.y}; }
        [[nodiscard]] constexpr Vec2 operator * (const Vec2& other) const noexcept { return {this->x * other.x, this->y * other.y}; }
        [[nodiscard]] constexpr Vec2 operator / (const Vec2& other) const noexcept { return {this->x / other.x, this->y / other.y}; }

        [[nodiscard]] constexpr Vec2 operator + (ValueT scalar) const noexcept { return {this->x + scalar, this->y + scalar}; }
        [[nodiscard]] constexpr Vec2 operator - (ValueT scalar) const noexcept { return {this->x - scalar, this->y - scalar}; }
        [[nodiscard]] constexpr Vec2 operator * (ValueT scalar) const noexcept { return {this->x * scalar, this->y * scalar}; }
        [[nodiscard]] constexpr Vec2 operator / (ValueT scalar) const noexcept { return {this->x / scalar, this->y / scalar}; }

        constexpr Vec2& operator += (const Vec2& other) noexcept { this->x += other.x; this->y += other.y; return *this; }
        constexpr Vec2& operator -= (const Vec2& other) noexcept { this->x -= other.x; this->y -= other.y; return *this; }
        constexpr Vec2& operator *= (const Vec2& other) noexcept { this->x *= other.x; this->y *= other.y; return *this; }
        constexpr Vec2& operator /= (const Vec2& other) noexcept { this->x /= other.x; this->y /= other.y; return *this; }

        constexpr Vec2& operator += (ValueT scalar) noexcept { this->x += scalar; this->y += scalar; return *this; }
        constexpr Vec2& operator -= (ValueT scalar) noexcept { this->x -= scalar; this->y -= scalar; return *this; }
        constexpr Vec2& operator *= (ValueT scalar) noexcept { this->x *= scalar; this->y *= scalar; return *this; }
        constexpr Vec2& operator /= (ValueT scalar) noexcept { this->x /= scalar; this->y /= scalar; return *this; }

        constexpr bool operator == (const Vec2& other) const noexcept = default;
        constexpr bool operator != (const Vec2& other) const noexcept = default;
    };

    /// @brief Scalar-vector addition.
    template <typename ValueT>
    constexpr Vec2<ValueT> operator+(ValueT scalar, const Vec2<ValueT>& vector) noexcept { return vector + scalar; }

    /// @brief Scalar-vector multiplication.
    template <typename ValueT>
    constexpr Vec2<ValueT> operator*(ValueT scalar, const Vec2<ValueT>& vector) noexcept { return vector * scalar; }

    /// @brief 2D vector with float components.
    using vec2f = Vec2<core::f32>;

    /// @brief 2D vector with integer components.
    using vec2i = Vec2<core::i32>;

} // namespace zen::math
