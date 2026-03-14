#pragma once

#include "../core/_export.hpp"
#include "../core/types.hpp"

namespace zen::math {

    /// @brief Converts an angle in degrees to radians.
    /// @param degrees Angle in degrees.
    /// @return Angle in radians.
    [[nodiscard]] constexpr f32 DegreesToRadians(f32 degrees) noexcept;

    /// @brief Converts an angle in radians to degrees.
    /// @param radians Angle in radians.
    /// @return Angle in degrees.
    [[nodiscard]] constexpr f32 RadiansToDegrees(f32 radians) noexcept;

    /// ---
    /// @brief Represents an angle stored internally in radians.
    /// The `Angle` type provides a type-safe abstraction over raw floating-point
    /// values when working with rotations or angular measurements.
    /// ---
    struct ZEN_API Angle {
    private:
        f32 _radians = 0.0f; ///< Internal angle value stored in radians

        /// @brief Constructs an angle directly from radians.
        /// This constructor is private to enforce the use of the
        /// `FromRadians` and `FromDegrees` factory functions.
        /// @param radians Angle value in radians.
        constexpr Angle(f32 radians) : _radians {radians} {}

    public:
        /// @brief Creates an angle from a radian value.
        /// @param radians Angle in radians.
        /// @return Angle instance representing the provided value.
        [[nodiscard]] static constexpr Angle FromRadians(f32 radians);

        /// @brief Creates an angle from a degree value.
        /// @param radians Angle in degrees.
        /// @return Angle instance representing the provided value.
        [[nodiscard]] static constexpr Angle FromDegrees(f32 degrees);

        /// @brief Returns the angle value in radians.
        /// @return Angle in radians.
        [[nodiscard]] constexpr f32 AsRadians() const;

        /// @brief Returns the angle value in degrees.
        /// @return Angle in degrees.
        [[nodiscard]] constexpr f32 AsDegrees() const;

        /// @brief Returns a normalized angle.
        /// Normalization ensures the angle lies within a standard range
        /// (typically `[0, 2π)`).
        /// @return Normalized angle.
        [[nodiscard]] Angle Normalized() const;

        /// @brief Computes the sine of the angle.
        /// @return Sine of the angle.
        [[nodiscard]] f32 Sin() const noexcept;

        /// @brief Computes the cosine of the angle.
        /// @return Cosine of the angle.
        [[nodiscard]] f32 Cos() const noexcept;

        /// @brief Computes the tangent of the angle.
        /// @return Tangent of the angle.
        [[nodiscard]] f32 Tan() const noexcept;

        [[nodiscard]] Angle operator + (Angle other) const;
        [[nodiscard]] Angle operator - (Angle other) const;
        [[nodiscard]] Angle operator * (f32 scalar) const;
        [[nodiscard]] Angle operator / (f32 scalar) const;

        Angle& operator += (Angle other);
        Angle& operator -= (Angle other);

        bool operator == (Angle other) const;
        bool operator != (Angle other) const;
        bool operator < (Angle other) const;
        bool operator > (Angle other) const;
        bool operator <= (Angle other) const;
        bool operator >= (Angle other) const;
    };

} // namespace zen::math
