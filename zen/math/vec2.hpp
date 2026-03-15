#pragma once

#include "angle.hpp"
#include "utils.hpp"
#include "../core/types.hpp"

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

        /// @brief Creates a unit vector from an angle.
        [[nodiscard]] static Vec2 FromAngle(const Angle& angle) noexcept
        {
            return {static_cast<ValueT>(angle.Cos()), static_cast<ValueT>(angle.Sin())};
        }

        /// @brief Returns a vector rotated 90 degrees counter-clockwise.
        [[nodiscard]] constexpr Vec2 Rotated90() const noexcept { return {-this->y, this->x}; }

        /// @brief Returns a vector rotated 270 degrees counter-clockwise.
        [[nodiscard]] constexpr Vec2 Rotated270() const noexcept { return {this->y, -this->x}; }

        /// @brief Rotates the vector by a given angle.
        [[nodiscard]] Vec2 Rotated(const Angle& rotationAngle) const noexcept
        {
            const f32 COS_VAL = rotationAngle.Cos();
            const f32 SIN_VAL = rotationAngle.Sin();

            return {
                static_cast<ValueT>(this->x * COS_VAL - this->y * SIN_VAL),
                static_cast<ValueT>(this->x * SIN_VAL + this->y * COS_VAL)
            };
        }

        /// @brief Component-wise minimum with another vector.
        [[nodiscard]] Vec2 Min(const Vec2& other) const noexcept
        {
            return {Min(this->x, other.x), Min(this->y, other.y)};
        }

        /// @brief Component-wise maximum with another vector.
        [[nodiscard]] Vec2 Max(const Vec2& other) const noexcept
        {
            return {Max(this->x, other.x), Max(this->y, other.y)};
        }

        /// @brief Returns absolute component values.
        [[nodiscard]] Vec2 Abs() const noexcept { return {std::abs(this->x), std::abs(this->y)}; }

        /// @brief Component-wise clamp between minVec and maxVec.
        [[nodiscard]] Vec2 Clamp(const Vec2& minVec, const Vec2& maxVec) const noexcept
        {
            return {Clamp(this->x, minVec.x, maxVec.x), Clamp(this->y, minVec.y, maxVec.y)};
        }

        /// @brief Component-wise remap from one range to another.
        [[nodiscard]] Vec2 Remap(
            const Vec2& inMin,
            const Vec2& inMax,
            const Vec2& outMin,
            const Vec2& outMax
        ) const noexcept
        {
            return {
                Remap(this->x, inMin.x, inMax.x, outMin.x, outMax.x),
                Remap(this->y, inMin.y, inMax.y, outMin.y, outMax.y)
            };
        }

        /// @brief Component-wise wrap between minVec and maxVec.
        [[nodiscard]] Vec2 Wrap(const Vec2& minVec, const Vec2& maxVec) const noexcept
        {
            return {Wrap(this->x, minVec.x, maxVec.x), Wrap(this->y, minVec.y, maxVec.y)};
        }

        /// @brief Component-wise smooth step interpolation between two vectors.
        [[nodiscard]] Vec2 SmoothStep(const Vec2& edge0, const Vec2& edge1) const noexcept
        {
            return {SmoothStep(edge0.x, edge1.x, this->x), SmoothStep(edge0.y, edge1.y, this->y)};
        }

        /// @brief Computes the dot product.
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

        /// @brief Squared magnitude of the vector.
        [[nodiscard]] constexpr ValueT LengthSquared() const noexcept
        {
            return this->x * this->x + this->y * this->y;
        }

        /// @brief Magnitude of the vector.
        [[nodiscard]] f32 Length() const noexcept
        {
            return std::hypot(static_cast<f32>(this->x), static_cast<f32>(this->y));
        }

        /// @brief Reciprocal of the vector length.
        [[nodiscard]] f32 LengthInverse() const noexcept
        {
            const f32 LENGTH_SQUARED = static_cast<f32>(this->LengthSquared());
            return (LENGTH_SQUARED == 0) ? 0.0f : 1.0f / std::sqrt(LENGTH_SQUARED);
        }

        /// @brief Distance squared to another vector.
        [[nodiscard]] ValueT DistanceSquared(const Vec2& other) const noexcept
        {
            ValueT dx = this->x - other.x;
            ValueT dy = this->y - other.y;
            return dx * dx + dy * dy;
        }

        /// @brief Distance to another vector.
        [[nodiscard]] f32 Distance(const Vec2& other) const noexcept { return (*this - other).Length(); }

        /// @brief Returns a normalized vector (zero if magnitude is near zero).
        [[nodiscard]] Vec2 Normalized() const noexcept
        {
            const f32 MAGNITUDE = this->Length();

            return (MAGNITUDE < constants::F32_NORMAL_EPSILON)
                ? Vec2::Zero()
                : *this / static_cast<ValueT>(MAGNITUDE)
            ;
        }

        /// @brief Computes angle between this and another vector.
        [[nodiscard]] Angle AngleBetween(const Vec2& other) const noexcept
        {
            const f32 DENOM = this->Length() * other.Length();
            if (DENOM == 0) return Angle::FromRadians(0);

            const f32 COS_VAL = static_cast<f32>(this->Dot(other)) / DENOM;
            return Angle::FromRadians(std::acos(Clamp(COS_VAL, -1.0f, 1.0f)));
        }

        /// @brief Computes signed angle between vectors.
        [[nodiscard]] Angle SignedAngle(const Vec2& other) const noexcept
        {
            return Angle::FromRadians(std::atan2(this->Cross(other), this->Dot(other)));
        }

        /// @brief Polar angle of the vector.
        [[nodiscard]] Angle GetAngle() const noexcept
        {
            return Angle::FromRadians(std::atan2(this->y, this->x));
        }

        /// @brief Reflect vector over a normal.
        [[nodiscard]] Vec2 Reflect(const Vec2& normal) const noexcept
        {
            return *this - normal * (static_cast<ValueT>(2) * this->Dot(normal));
        }

        /// @brief Projects vector onto another vector.
        [[nodiscard]] Vec2 Project(const Vec2& other) const noexcept
        {
            const ValueT DENOM = other.LengthSquared();
            return (DENOM == 0) ? Vec2::Zero() : other * (this->Dot(other) / DENOM);
        }

        /// @brief Clamps vector length to a maximum.
        [[nodiscard]] Vec2 ClampLength(ValueT maxLength) const noexcept
        {
            const ValueT LEN_SQUARED = this->LengthSquared();
            return (LEN_SQUARED > maxLength * maxLength) ? this->Normalized() * maxLength : *this;
        }

        /// @brief Linear interpolation between two vectors.
        [[nodiscard]] static constexpr Vec2 Lerp(const Vec2& start, const Vec2& end, ValueT travel) noexcept
        {
            return {Lerp(start.x, end.x, travel), Lerp(start.y, end.y, travel)};
        }

        /// @brief Smoothly moves vector towards a target.
        [[nodiscard]] Vec2 SmoothDamp(const Vec2& target, ValueT smoothing) const noexcept
        {
            return Lerp(*this, target, smoothing);
        }

        /// @brief Moves vector towards target by a maximum delta.
        [[nodiscard]] Vec2 MoveTowards(const Vec2& target, ValueT maxDelta) const noexcept
        {
            const Vec2 DELTA = target - *this;
            const ValueT DELTA_MAGNITUDE_SQUARED = DELTA.LengthSquared();

            return (DELTA_MAGNITUDE_SQUARED == 0 || DELTA_MAGNITUDE_SQUARED <= maxDelta * maxDelta)
                ? target
                : *this + DELTA.Normalized() * maxDelta
            ;
        }

        /// @brief Slides vector along a surface normal.
        [[nodiscard]] Vec2 Slide(const Vec2& normal) const noexcept
        {
            return *this - normal * this->Dot(normal);
        }

        /// @brief Refracts vector with a given normal and ratio.
        [[nodiscard]] Vec2 Refract(const Vec2& normal, ValueT eta) const noexcept
        {
            const ValueT COS_I  = -this->Dot(normal);
            const ValueT SIN_T2 = eta * eta * (1 - COS_I * COS_I);

            return (SIN_T2 > 1)
                ? Vec2::Zero()
                : *this * eta + normal * (eta * COS_I - std::sqrt(1 - SIN_T2))
            ;
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

    template <typename ValueT>
    constexpr Vec2<ValueT> operator+(ValueT scalar, const Vec2<ValueT>& vector) noexcept { return vector + scalar; }

    template <typename ValueT>
    constexpr Vec2<ValueT> operator*(ValueT scalar, const Vec2<ValueT>& vector) noexcept { return vector * scalar; }

    /// @brief 2D vector with float components.
    using Vec2f = Vec2<f32>;

    /// @brief 2D vector with integer components.
    using Vec2i = Vec2<i32>;

    /// @brief Computes the dot product of two vectors.
    /// @note (AxBx + AyBy)
    template <typename ValueT>
    [[nodiscard]] constexpr ValueT DotProduct(const Vec2<ValueT>& lhs, const Vec2<ValueT>& rhs) noexcept
    {
        return lhs.x * rhs.x + lhs.y * rhs.y;
    }

    /// @brief Computes the cross product of two vectors.
    /// @note (AxBy - AyBx)
    template <typename ValueT>
    [[nodiscard]] constexpr ValueT CrossProduct(const Vec2<ValueT>& lhs, const Vec2<ValueT>& rhs) noexcept
    {
        return lhs.x * rhs.y - lhs.y * rhs.x;
    }

    /// @brief Returns true if two vectors are approximately equal.
    /// @note Used for vectors with floating point components.
    template <typename ValueT>
    [[nodiscard]] inline bool NearlyEqual(
        const Vec2<ValueT>& lhs,
        const Vec2<ValueT>& rhs,
        f32 epsilon = constants::F32_COMPARE_EPSILON
    ) noexcept
    {
        if constexpr (std::is_integral_v<ValueT>) return lhs.x == rhs.x && lhs.y == rhs.y;
        return NearlyEqual(lhs.x, rhs.x, epsilon) && NearlyEqual(lhs.y, rhs.y, epsilon);
    }

} // namespace zen::math
