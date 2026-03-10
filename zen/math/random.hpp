#pragma once

#include "../core/_export.hpp"
#include "../core/types.hpp"
#include "constants.hpp"

#include <algorithm>
#include <iterator>
#include <random>
#include <type_traits>

namespace zen::random
{

    [[nodiscard]] ZEN_API std::mt19937& GetEngine() noexcept;

    [[nodiscard]] ZEN_API u64 GenerateSeed();
    ZEN_API void SetSeed(u32 value);

    template <typename NumericT>
        requires std::is_integral_v<NumericT> || std::is_floating_point_v<NumericT>
    [[nodiscard]] NumericT Range(NumericT min, NumericT max)
    {
        if (min > max) std::swap(min, max);

        auto& engine = GetEngine();

        if constexpr (std::is_integral_v<NumericT>)
            return std::uniform_int_distribution<NumericT>{min, max}(engine);
        else
            return std::uniform_real_distribution<NumericT>{min, max}(engine);
    }

    [[nodiscard]] ZEN_API i32 RangeI32(i32 min = I32_MIN, i32 max = I32_MAX);
    [[nodiscard]] ZEN_API i64 RangeI64(i64 min = I64_MIN, i64 max = I64_MAX);

    [[nodiscard]] ZEN_API u32 RangeU32(u32 min = 0, u32 max = U32_MAX);
    [[nodiscard]] ZEN_API u64 RangeU64(u64 min = 0, u64 max = U64_MAX);

    [[nodiscard]] ZEN_API f32 RangeF32(f32 min = F32_MIN, f32 max = F32_MAX);
    [[nodiscard]] ZEN_API f64 RangeF64(f64 min = F64_MIN, f64 max = F64_MAX);

    [[nodiscard]] ZEN_API f32 UnitF32();
    [[nodiscard]] ZEN_API f64 UnitF64();

    [[nodiscard]] ZEN_API f32 NormalF32(f32 mean, f32 standardDeviation);
    [[nodiscard]] ZEN_API f64 NormalF64(f64 mean, f64 standardDeviation);

    [[nodiscard]] ZEN_API i32 SignI32();
    [[nodiscard]] ZEN_API f32 SignF32();

    [[nodiscard]] ZEN_API usize Index(usize size);

    [[nodiscard]] ZEN_API bool Boolean();
    [[nodiscard]] ZEN_API bool Chance(f32 probability);

    template <typename Iterator>
    void Shuffle(Iterator begin, Iterator end) { std::shuffle(begin, end, GetEngine()); }

    template <typename Iterator>
    [[nodiscard]] Iterator ChoiceIt(Iterator begin, Iterator end)
    {
        using DiffSizeT = typename std::iterator_traits<Iterator>::difference_type;

        DiffSizeT size = std::distance(begin, end);
        if (size <= 0) throw std::invalid_argument{"Container is empty"};

        if constexpr (std::random_access_iterator<Iterator>)
            return begin + Index(size);

        std::advance(begin, Index(size));
        return begin;
    }

    template <typename ValueContainerIterator, typename WeightContainerIterator>
    [[nodiscard]] auto& WeightedChoiceIt(
        ValueContainerIterator valuesBegin, ValueContainerIterator valuesEnd,
        WeightContainerIterator weightsBegin, WeightContainerIterator weightsEnd
    )
    {
        using ValueDiffSizeT = typename std::iterator_traits<ValueContainerIterator>::difference_type;
        ValueDiffSizeT valuesSize = std::distance(valuesBegin, valuesEnd);

        using WeightDiffSizeT = typename std::iterator_traits<WeightContainerIterator>::difference_type;
        WeightDiffSizeT weightsSize = std::distance(weightsBegin, weightsEnd);

        if (valuesSize != weightsSize)
            throw std::invalid_argument{"Values and Weight size mismatch"};
        if (valuesSize == 0)
            throw std::invalid_argument{"Container is empty"};

        std::discrete_distribution<usize> distribution {weightsBegin, weightsEnd};

        if constexpr (std::random_access_iterator<ValueContainerIterator>)
            return valuesBegin + distribution(GetEngine());

        std::advance(valuesBegin, distribution(GetEngine()));
        return valuesBegin;
    }

    template <typename Container>
    [[nodiscard]] auto& Choice(Container& values) { return *ChoiceIt(values.begin(), values.end()); }

    template <typename Container>
    [[nodiscard]] const auto& Choice(const Container& values) { return *ChoiceIt(values.cbegin(), values.cend()); }

    template <typename Iterator>
    [[nodiscard]] auto& Choice(Iterator begin, Iterator end) { return *ChoiceIt(begin, end); }

    template <typename Container, typename WeightContainer>
    [[nodiscard]] auto& WeightedChoice(Container& values, const WeightContainer& weights)
    {
        return *WeightedChoiceIt(values.begin(), values.end(), weights.cbegin(), weights.cend());
    }

    template <typename Container, typename WeightContainer>
    [[nodiscard]] const auto& WeightedChoice(const Container& values, const WeightContainer& weights)
    {
        return *WeightedChoiceIt(values.cbegin(), values.cend(), weights.cbegin(), weights.cend());
    }

    template <typename ValueContainerIterator, typename WeightContainerIterator>
    [[nodiscard]] const auto& WeightedChoice(
        ValueContainerIterator valuesBegin, ValueContainerIterator valuesEnd,
        WeightContainerIterator weightsBegin, WeightContainerIterator weightsEnd
    )
    {
        return *WeightedChoiceIt(valuesBegin, valuesEnd, weightsBegin, weightsEnd);
    }

} // namespace zen::random
