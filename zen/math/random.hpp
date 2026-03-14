#pragma once

#include "constants.hpp"
#include "../core/_export.hpp"
#include "../core/types.hpp"
#include "../container/iterator_wrapper.hpp"

#include <iterator>
#include <random>
#include <type_traits>

namespace zen::random {

    /// @brief Returns the global random engine used by the library.
    /// @return Reference to the internal std::mt19937 engine.
    [[nodiscard]] ZEN_API std::mt19937& GetEngine() noexcept;

    /// @brief Generates a random seed using system entropy.
    /// @return 64-bit seed value.
    [[nodiscard]] ZEN_API u32 GenerateSeed();

    /// @brief Sets the seed for the global random engine.
    /// @param value Seed value.
    ZEN_API void SetSeed(u32 value);

    /// @brief Generates a uniformly distributed random value.
    /// @tparam NumericT Numeric type (integral or floating point).
    /// @param min Minimum value.
    /// @param max Maximum value.
    /// @return Random value within the specified range.
    template <typename NumericT>
        requires std::is_arithmetic_v<NumericT>
    [[nodiscard]] NumericT UniformDistribution(NumericT min, NumericT max)
    {
        if (min > max) std::swap(min, max);

        if constexpr (std::is_integral_v<NumericT>)
            return std::uniform_int_distribution<NumericT>{min, max}(GetEngine());
        else
            return std::uniform_real_distribution<NumericT>{min, max}(GetEngine());
    }

    /// @brief Generates a normally distributed random value.
    /// @tparam NumericT Numeric type.
    /// @param mean Mean value of the distribution.
    /// @param standardDeviation Standard deviation.
    /// @return Random value following a normal distribution.
    template <typename NumericT>
        requires std::is_arithmetic_v<NumericT>
    [[nodiscard]] NumericT NormalDistribution(NumericT mean, NumericT standardDeviation)
    {
        return std::normal_distribution<NumericT>{mean, standardDeviation}(GetEngine());
    }

    /// @brief Generates an index using a discrete weighted distribution.
    /// @tparam WeightsIt Iterator type for weight values.
    /// @param weights Iterator wrapper containing weight values.
    /// @return Selected index based on weight distribution.
    template <typename WeightsIt>
    [[nodiscard]] size_t DiscreteDistribution(const container::IteratorWrapper<WeightsIt>& weights)
    {
        return std::discrete_distribution<size_t>{weights.GetBegin(), weights.GetEnd()}(GetEngine());
    }

    /// @brief Generates a random 32-bit signed integer.
    /// @param min Minimum value.
    /// @param max Maximum value.
    /// @return Random i32 within the specified range.
    [[nodiscard]] ZEN_API i32 RangeI32(
        i32 min = constants::I32_MIN, i32 max = constants::I32_MAX
    );

    /// @brief Generates a random 64-bit signed integer.
    [[nodiscard]] ZEN_API i64 RangeI64(
        i64 min = constants::I64_MIN, i64 max = constants::I64_MAX
    );

    /// @brief Generates a random 32-bit unsigned integer.
    [[nodiscard]] ZEN_API u32 RangeU32(u32 min = 0, u32 max = constants::U32_MAX);

    /// @brief Generates a random 64-bit unsigned integer.
    [[nodiscard]] ZEN_API u64 RangeU64(u64 min = 0, u64 max = constants::U64_MAX);

    /// @brief Generates a random 32-bit floating-point value.
    [[nodiscard]] ZEN_API f32 RangeF32(
        f32 min = constants::F32_MIN, f32 max = constants::F32_MAX
    );

    /// @brief Generates a random 64-bit floating-point value.
    [[nodiscard]] ZEN_API f64 RangeF64(
        f64 min = constants::F64_MIN, f64 max = constants::F64_MAX
    );

    /// @brief Generates a floating-point value in the range [0,1].
    [[nodiscard]] ZEN_API f32 UnitF32();

    /// @brief Generates a floating-point value in the range [0,1].
    [[nodiscard]] ZEN_API f64 UnitF64();

    /// @brief Generates a normally distributed 32-bit floating-point value.
    [[nodiscard]] ZEN_API f32 NormalF32(f32 mean, f32 standardDeviation);

    /// @brief Generates a normally distributed 64-bit floating-point value.
    [[nodiscard]] ZEN_API f64 NormalF64(f64 mean, f64 standardDeviation);

    /// @brief Generates either -1 or +1.
    /// @return Random sign value.
    [[nodiscard]] ZEN_API i32 SignI32();

    /// @brief Generates either -1.0f or +1.0f.
    [[nodiscard]] ZEN_API f32 SignF32();

    /// @brief Generates a random index for a container of given size.
    /// @param size Container size.
    /// @return Random index in range [0, size).
    [[nodiscard]] ZEN_API usize Index(usize size);

    /// @brief Generates a random boolean value.
    /// @return true or false with equal probability.
    [[nodiscard]] ZEN_API bool Boolean();

    /// @brief Returns true based on a probability threshold.
    /// @param probability Value in range [0,1].
    /// @return true with the given probability.
    [[nodiscard]] ZEN_API bool Chance(f32 probability);

    /// @brief Randomly shuffles a range of elements.
    /// @tparam IteratorT Iterator type.
    /// @param begin Start of range.
    /// @param end End of range.
    template <typename IteratorT>
    void Shuffle(IteratorT begin, IteratorT end) { std::shuffle(begin, end, GetEngine()); }

    /// @brief Selects a random element from an iterator range.
    /// @tparam IteratorT Iterator type.
    /// @param wrapper Iterator wrapper containing the range.
    /// @return Reference to the selected element.
    template <std::forward_iterator IteratorT>
    [[nodiscard]] container::IteratorWrapper<IteratorT>::reference ChoiceIt(
        const container::IteratorWrapper<IteratorT>& wrapper
    ) {
        usize index = Index(wrapper.GetSize());
        return wrapper[index];
    }

    /// @brief Selects a random element from an iterator pair.
    template <std::forward_iterator IteratorT>
    [[nodiscard]] auto& Choice(IteratorT begin, IteratorT end)
    {
        return ChoiceIt(container::IteratorWrapper<IteratorT>{begin, end});
    }

    /// @brief Selects a random element from a container.
    template <typename ContainerT>
    [[nodiscard]] auto& Choice(ContainerT& container)
    {
        return ChoiceIt(container::IteratorWrapper{container});
    }

    /// @brief Selects a random element from a const container.
    template <typename ContainerT>
    [[nodiscard]] const auto& Choice(const ContainerT& container)
    {
        return ChoiceIt(container::IteratorWrapper{container});
    }

    /// @brief Selects a random element from an initializer list.
    template <typename ValueT>
    [[nodiscard]] const ValueT& Choice(std::initializer_list<ValueT> initList)
    {
        return ChoiceIt(container::IteratorWrapper{initList.begin(), initList.end()});
    }

    /// @brief Selects a random element using weighted probabilities.
    /// @tparam ValuesIt Iterator type for values.
    /// @tparam WeightsIt Iterator type for weights.
    /// @return Reference to the selected value.
    template <std::forward_iterator ValuesIt, std::forward_iterator WeightsIt>
    [[nodiscard]] container::IteratorWrapper<ValuesIt>::reference WeightedChoiceIt(
        const container::IteratorWrapper<ValuesIt>& values,
        const container::IteratorWrapper<WeightsIt>& weights
    ) {
        if (values.GetSize() == weights.GetSize()) return values[DiscreteDistribution(weights)];
        throw std::invalid_argument{"Value and weight containers must have same size"};
    }

    /// @brief Selects a random element using weighted probabilities.
    /// @tparam ValuesIt Iterator type for values.
    /// @tparam WeightsIt Iterator type for weights.
    /// @return Reference to the selected value.
    template <std::forward_iterator ValuesIt, std::forward_iterator WeightsIt>
    [[nodiscard]] auto& WeightedChoice(
        ValuesIt valuesBegin, ValuesIt valuesEnd,
        WeightsIt weightsBegin, WeightsIt weightsEnd
    ) {
        return WeightedChoiceIt(
            container::IteratorWrapper{valuesBegin, valuesEnd},
            container::IteratorWrapper{weightsBegin, weightsEnd}
        );
    }

    /// @brief Selects a random element using weighted probabilities.
    /// @tparam ValueContainerT container type of values.
    /// @tparam WeightContainerT container type of weights.
    /// @return Reference to the selected value.
    template <typename ValueContainerT, typename WeightContainerT>
    [[nodiscard]] auto& WeightedChoice(ValueContainerT& values, WeightContainerT& weights)
    {
        return WeightedChoiceIt(container::IteratorWrapper{values}, container::IteratorWrapper{weights});
    }

    /// @brief Selects a random element using weighted probabilities.
    /// @tparam ValueContainerT container type of values.
    /// @tparam WeightContainerT container type of weights.
    /// @return Reference to the selected value.
    template <typename ValueContainerT, typename WeightContainerT>
    [[nodiscard]] const auto& WeightedChoice(const ValueContainerT& values, const WeightContainerT& weights)
    {
        return WeightedChoiceIt(container::IteratorWrapper{values}, container::IteratorWrapper{weights});
    }

    /// @brief Selects a random element using weighted probabilities.
    /// @tparam ValueT type of values.
    /// @tparam WeightT type of weights.
    /// @param valueInitList Initializer list of values.
    /// @param weightInitList Initializer list of weights.
    /// @return Reference to the selected value.
    template <typename ValueT, typename WeightT>
    [[nodiscard]] const ValueT& WeightedChoice(
        std::initializer_list<ValueT> valueInitList,
        std::initializer_list<WeightT> weightInitList
    ) {
        return WeightedChoiceIt(
            container::IteratorWrapper{valueInitList.begin(), valueInitList.end()},
            container::IteratorWrapper{weightInitList.begin(), weightInitList.end()}
        );
    }

} // namespace zen::random
