#pragma once

#include "../core/_export.hpp"
#include "../core/types.hpp"

namespace zen::math {

    /// @brief Converts an angle in degrees to radians.
    /// @param degrees Angle in degrees.
    /// @return Angle in radians.
    [[nodiscard]] constexpr core::f32 DegreesToRadians(core::f32 degrees) noexcept;

    /// @brief Converts an angle in radians to degrees.
    /// @param radians Angle in radians.
    /// @return Angle in degrees.
    [[nodiscard]] constexpr core::f32 RadiansToDegrees(core::f32 radians) noexcept;

    /// ---
    /// @brief Represents an angle stored internally in radians.
    /// The `Angle` type provides a type-safe abstraction over raw floating-point
    /// values when working with rotations or angular measurements.
    /// ---
    struct ZEN_API Angle {
    private:
        core::f32 _radians = 0.0f; ///< Internal angle value stored in radians

        /// @brief Constructs an angle directly from radians.
        /// This constructor is private to enforce the use of the
        /// `FromRadians` and `FromDegrees` factory functions.
        /// @param radians Angle value in radians.
        constexpr Angle(core::f32 radians) : _radians {radians} {}

    public:
        /// @brief Creates an angle from a radian value.
        /// @param radians Angle in radians.
        /// @return Angle instance representing the provided value.
        [[nodiscard]] static constexpr Angle FromRadians(core::f32 radians);

        /// @brief Creates an angle from a degree value.
        /// @param radians Angle in degrees.
        /// @return Angle instance representing the provided value.
        [[nodiscard]] static constexpr Angle FromDegrees(core::f32 degrees);

        /// @brief Returns the angle value in radians.
        /// @return Angle in radians.
        [[nodiscard]] constexpr core::f32 AsRadians() const;

        /// @brief Returns the angle value in degrees.
        /// @return Angle in degrees.
        [[nodiscard]] constexpr core::f32 AsDegrees() const;

        /// @brief Returns a normalized angle.
        /// Normalization ensures the angle lies within a standard range
        /// (typically `[0, 2π)`).
        /// @return Normalized angle.
        [[nodiscard]] Angle Normalized() const;

        /// @brief Computes the sine of the angle.
        /// @return Sine of the angle.
        [[nodiscard]] core::f32 Sin() noexcept;

        /// @brief Computes the cosine of the angle.
        /// @return Cosine of the angle.
        [[nodiscard]] core::f32 Cos() noexcept;

        /// @brief Computes the tangent of the angle.
        /// @return Tangent of the angle.
        [[nodiscard]] core::f32 Tan() noexcept;

        /// @brief operation overload: Addition
        [[nodiscard]] Angle operator + (Angle other) const;

        /// @brief operation overload: Subtraction
        [[nodiscard]] Angle operator - (Angle other) const;

        /// @brief operation overload: Multiplication
        [[nodiscard]] Angle operator * (core::f32 scalar) const;

        /// @brief operation overload: Divison
        [[nodiscard]] Angle operator / (core::f32 scalar) const;

        /// @brief Performs addition operation and assign's result to self
        Angle& operator += (Angle other);

        /// @brief Performs subtraction operation and assign's result to self
        Angle& operator -= (Angle other);

        /// @brief Equality comparison within two angles
        [[nodiscard]] bool operator == (Angle other) const;

        /// @brief Inequality comparison within two angles
        [[nodiscard]] bool operator != (Angle other) const;

        /// @brief Lesser than comparison within 2 angles
        [[nodiscard]] bool operator < (Angle other) const;

        /// @brief Greater than comparison within 2 angles
        [[nodiscard]] bool operator > (Angle other) const;

        /// @brief Greater than or Equal comparison within 2 angles
        [[nodiscard]] bool operator <= (Angle other) const;

        /// @brief Lesser than or Equal comparison within 2 angles
        [[nodiscard]] bool operator >= (Angle other) const;
    };

} // namespace zen::math
