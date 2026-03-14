#pragma once

#include "constants.hpp"
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
        constexpr Vec2(ValueT x, ValueT y) noexcept : x {x}, y {y} {}

        /// @brief Returns a zero vector.
        [[nodiscard]] static constexpr Vec2 Zero() noexcept { return {0, 0}; }

        /// @brief Returns a vector with all components equal to 1.
        [[nodiscard]] static constexpr Vec2 One() noexcept { return {1, 1}; }

        /// @brief Returns the unit vector pointing upward.
        [[nodiscard]] static constexpr Vec2 Up() noexcept { return {0, 1}; }

        /// @brief Returns the unit vector pointing downward.
        [[nodiscard]] static constexpr Vec2 Down() noexcept { return {0, -1}; }

        /// @brief Returns the unit vector pointing left.
        [[nodiscard]] static constexpr Vec2 Left() noexcept { return {-1, 0}; }

        /// @brief Returns the unit vector pointing right.
        [[nodiscard]] static constexpr Vec2 Right() noexcept { return {1, 0}; }

        /// @brief Returns a vector where both components equal the specified value.
        /// @param val Value for both components.
        [[nodiscard]] static constexpr Vec2 Unit(ValueT val = 1) noexcept { return {val, val}; }

        /// @brief Computes the dot product between two vectors.
        /// @param other Other vector.
        /// @return Scalar dot product.
        [[nodiscard]] constexpr ValueT Dot(const Vec2& other) const noexcept
        {
            return this->x * other.x + this->y * other.y;
        }

        /// @brief Computes the 2D cross product (scalar).
        /// @param other Other vector.
        /// @return Scalar cross product.
        [[nodiscard]] constexpr ValueT Cross(const Vec2& other) const noexcept
        {
            return this->x * other.y - this->y * other.x;
        }

        /// @brief Returns a perpendicular vector.
        /// Rotates the vector 90 degrees counter-clockwise.
        /// @return Perpendicular vector.
        [[nodiscard]] constexpr Vec2 Perpendicular() const noexcept { return {-this->y, this->x}; }

        /// @brief Computes the length (magnitude) of the vector.
        /// @return Vector length.
        [[nodiscard]] ValueT Length() const noexcept { return std::hypot(this->x, this->y); }

        /// @brief Computes the distance between two vectors.
        /// @param other Other vector.
        /// @return Distance between vectors.
        [[nodiscard]] ValueT Distance(const Vec2& other) const noexcept { return (*this - other).Length(); }

        /// @brief Returns a normalized version of the vector.
        /// If the vector length is zero, a zero vector is returned.
        /// @return Unit-length vector.
        [[nodiscard]] Vec2 Normalized() const noexcept
        {
            const ValueT CURRENT_LENGTH = this->Length();
            return CURRENT_LENGTH ? (*this / CURRENT_LENGTH) : Vec2::Zero();
        }

        /// @brief Normalizes the vector in-place.
        void Normalize() noexcept { *this = this->Normalized(); }

        /// @brief Checks if two vectors are approximately equal.
        ///
        /// For floating point types an epsilon comparison is used.
        ///
        /// @param other Other vector.
        /// @param epsilon Allowed error tolerance.
        /// @return True if vectors are nearly equal.
        [[nodiscard]] bool NearlyEquals(
            const Vec2& other,
            core::f32 epsilon = constants::F32_EPSILON
        ) const noexcept
        {
            if constexpr (!std::is_floating_point_v<ValueT>)
                return this->x == other.x && this->y == other.y;
            else
                return CompareF32Eq(this->x, other.x, epsilon) && CompareF32Eq(this->y, other.y, epsilon);
        }

        /// @brief Unary negation operator.
        [[nodiscard]] constexpr Vec2 operator - () const noexcept { return {-x, -y}; }

        /// @brief Vector addition.
        [[nodiscard]] constexpr Vec2 operator + (const Vec2& other) const noexcept
        {
            return {this->x + other.x, this->y + other.y};
        }

        /// @brief Vector subtraction.
        [[nodiscard]] constexpr Vec2 operator - (const Vec2& other) const noexcept
        {
            return {this->x - other.x, this->y - other.y};
        }

        /// @brief Component-wise multiplication.
        [[nodiscard]] constexpr Vec2 operator * (const Vec2& other) const noexcept
        {
            return {this->x * other.x, this->y * other.y};
        }

        /// @brief Component-wise division.
        [[nodiscard]] constexpr Vec2 operator / (const Vec2& other) const noexcept
        {
            return {this->x / other.x, this->y / other.y};
        }

        constexpr Vec2& operator += (const Vec2& other) noexcept { return *this = *this + other; }
        constexpr Vec2& operator -= (const Vec2& other) noexcept { return *this = *this - other; }
        constexpr Vec2& operator *= (const Vec2& other) noexcept { return *this = *this * other; }
        constexpr Vec2& operator /= (const Vec2& other) noexcept { return *this = *this / other; }

        /// @brief Adds a scalar to both components.
        [[nodiscard]] constexpr Vec2 operator + (ValueT scalar) const noexcept
        {
            return {this->x + scalar, this->y + scalar};
        }

        /// @brief Subtracts a scalar from both components.
        [[nodiscard]] constexpr Vec2 operator - (ValueT scalar) const noexcept
        {
            return {this->x - scalar, this->y - scalar};
        }

        /// @brief Multiplies both components by a scalar.
        [[nodiscard]] constexpr Vec2 operator * (ValueT scalar) const noexcept
        {
            return {this->x * scalar, this->y * scalar};
        }

        /// @brief Divides both components by a scalar.
        [[nodiscard]] constexpr Vec2 operator / (ValueT scalar) const noexcept
        {
            return {this->x / scalar, this->y / scalar};
        }

        constexpr Vec2& operator += (ValueT scalar) noexcept { x += scalar; y += scalar; return *this; }
        constexpr Vec2& operator -= (ValueT scalar) noexcept { x -= scalar; y -= scalar; return *this; }
        constexpr Vec2& operator *= (ValueT scalar) noexcept { x *= scalar; y *= scalar; return *this; }
        constexpr Vec2& operator /= (ValueT scalar) noexcept { x /= scalar; y /= scalar; return *this; }

        /// @brief Equality comparison.
        constexpr bool operator == (const Vec2& other) const noexcept = default;

        /// @brief Inequality comparison.
        constexpr bool operator != (const Vec2& other) const noexcept = default;
    };

    /// @brief Adds a scalar to a vector.
    template <typename T>
    constexpr Vec2<T> operator + (T scalar, const Vec2<T>& vector) noexcept { return vector + scalar; }

    /// @brief Multiplies a vector by a scalar.
    template <typename T>
    constexpr Vec2<T> operator * (T scalar, const Vec2<T>& vector) noexcept { return vector * scalar; }

    /// @brief 2D vector with float components.
    using vec2f = Vec2<core::f32>;

    /// @brief 2D vector with integer components.
    using vec2i = Vec2<core::i32>;

} // namespace zen::math
