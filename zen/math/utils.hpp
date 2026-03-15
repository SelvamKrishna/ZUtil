#pragma once

#include "constants.hpp"
#include "../core/types.hpp"

#include <cmath>
#include <type_traits>

namespace zen::math {

    /// @brief Returns true if two 32-bit floats are approximately equal.
    [[nodiscard]] inline bool NearlyEqual(
        f32 lhs,
        f32 rhs,
        f32 epsilon = constants::F32_COMPARE_EPSILON
    ) noexcept
    {
        return std::abs(lhs - rhs) <= epsilon;
    }

    /// @brief Returns true if two 64-bit floats are approximately equal.
    [[nodiscard]] inline bool NearlyEqual(
        f64 lhs,
        f64 rhs,
        f64 epsilon = constants::F64_COMPARE_EPSILON
    ) noexcept
    {
        return std::abs(lhs - rhs) <= epsilon;
    }

    /// @brief Clamps a value between a minimum and maximum bound.
    template<typename ValueT>
        requires std::is_arithmetic_v<ValueT>
    [[nodiscard]] inline constexpr ValueT Clamp(ValueT value, ValueT minValue, ValueT maxValue) noexcept
    {
        return (value < minValue) ? minValue : (value > maxValue) ? maxValue : value;
    }

    /// @brief Returns the smaller of two values.
    template<typename ValueT>
        requires std::is_arithmetic_v<ValueT>
    [[nodiscard]] inline constexpr ValueT Min(ValueT valueA, ValueT valueB) noexcept
    {
        return (valueA < valueB) ? valueA : valueB;
    }

    /// @brief Returns the larger of two values.
    template<typename ValueT>
        requires std::is_arithmetic_v<ValueT>
    [[nodiscard]] inline constexpr ValueT Max(ValueT valueA, ValueT valueB) noexcept
    {
        return (valueA > valueB) ? valueA : valueB;
    }

    /// @brief Returns the sign of a value (-1, 0, 1).
    template<typename ValueT>
        requires std::is_arithmetic_v<ValueT>
    [[nodiscard]] inline constexpr int Sign(ValueT value) noexcept
    {
        return (ValueT(0) < value) - (value < ValueT(0));
    }

    /// @brief Performs linear interpolation between two values.
    template<typename ValueT>
        requires std::is_arithmetic_v<ValueT>
    [[nodiscard]] inline constexpr ValueT Lerp(ValueT startValue, ValueT endValue, ValueT travel) noexcept
    {
        return startValue + (endValue - startValue) * travel;
    }

    /// @brief Computes the normalized interpolation factor between two values.
    template<typename ValueT>
        requires std::is_arithmetic_v<ValueT>
    [[nodiscard]] inline constexpr ValueT InverseLerp(ValueT startValue, ValueT endValue, ValueT value) noexcept
    {
        return (value - startValue) / (endValue - startValue);
    }

    /// @brief Remaps a value from one range into another range.
    template<typename ValueT>
        requires std::is_arithmetic_v<ValueT>
    [[nodiscard]] inline constexpr ValueT Remap(
        ValueT value,
        ValueT inMin,
        ValueT inMax,
        ValueT outMin,
        ValueT outMax
    ) noexcept
    {
        return outMin + (value - inMin) * (outMax - outMin) / (inMax - inMin);
    }

    /// @brief Wraps a value inside the range [min, max).
    template<typename ValueT>
        requires std::is_arithmetic_v<ValueT>
    [[nodiscard]] inline ValueT Wrap(ValueT value, ValueT minValue, ValueT maxValue) noexcept
    {
        const ValueT RANGE = maxValue - minValue;
        if (RANGE == 0) return minValue;

        value = std::fmod(value - minValue, RANGE);
        if (value < 0) value += RANGE;

        return value + minValue;
    }

    /// @brief Repeats a value within the interval [0, length).
    template<typename ValueT>
        requires std::is_arithmetic_v<ValueT>
    [[nodiscard]] inline ValueT Repeat(ValueT value, ValueT length) noexcept
    {
        return value - std::floor(value / length) * length;
    }

    /// @brief Computes a smooth interpolation curve between two edges.
    template<typename ValueT>
        requires std::is_arithmetic_v<ValueT>
    [[nodiscard]] inline ValueT SmoothStep(ValueT edgeStart, ValueT edgeEnd, ValueT value) noexcept
    {
        const ValueT TRAVEL = Clamp((value - edgeStart) / (edgeEnd - edgeStart), ValueT(0), ValueT(1));
        return TRAVEL * TRAVEL * (ValueT(3) - ValueT(2) * TRAVEL);
    }

} // namespace zen::math
