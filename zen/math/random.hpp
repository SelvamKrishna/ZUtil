#pragma once

#include "../core/_export.hpp"
#include "../core/types.hpp"
#include "../container/iterator_wrapper.hpp"
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

    template <typename IteratorT>
    void Shuffle(IteratorT begin, IteratorT end) { std::shuffle(begin, end, GetEngine()); }

    template <std::forward_iterator IteratorT>
    [[nodiscard]] IteratorWrapper<IteratorT>::reference ChoiceIt(const IteratorWrapper<IteratorT>& wrapper)
    {
        usize index = Index(wrapper.GetSize());
        return wrapper[index];
    }

    template <std::forward_iterator IteratorT>
    [[nodiscard]] auto& Choice(IteratorT begin, IteratorT end)
    {
        return ChoiceIt(IteratorWrapper<IteratorT>{begin, end});
    }

    template <typename ContainerT>
    [[nodiscard]] auto& Choice(ContainerT& container)
    {
        return ChoiceIt(IteratorWrapper{container});
    }

    template <typename ContainerT>
    [[nodiscard]] const auto& Choice(const ContainerT& container)
    {
        return ChoiceIt(IteratorWrapper{container});
    }

    template <typename ValueT>
    [[nodiscard]] const ValueT& Choice(std::initializer_list<ValueT> initList)
    {
        return ChoiceIt(IteratorWrapper{initList.begin(), initList.end()});
    }

    template <std::forward_iterator ValuesIt, std::forward_iterator WeightsIt>
    [[nodiscard]] IteratorWrapper<ValuesIt>::reference WeightedChoiceIt(
        const IteratorWrapper<ValuesIt>& values,
        const IteratorWrapper<WeightsIt>& weights
    )
    {
        if (values.GetSize() != weights.GetSize())
            throw std::invalid_argument{"Value and weight containers must have same size"};

        std::discrete_distribution<usize> distribution {weights.GetBegin(), weights.GetEnd()};
        return values[distribution(GetEngine())];
    }

    template <std::forward_iterator ValuesIt, std::forward_iterator WeightsIt>
    [[nodiscard]] auto& WeightedChoice(
        ValuesIt valuesBegin, ValuesIt valuesEnd,
        WeightsIt weightsBegin, WeightsIt weightsEnd
    )
    {
        return WeightedChoiceIt(
            IteratorWrapper{valuesBegin, valuesEnd},
            IteratorWrapper{weightsBegin, weightsEnd}
        );
    }

    template <typename ValueContainerT, typename WeightContainerT>
    [[nodiscard]] auto& WeightedChoice(ValueContainerT& values, WeightContainerT& weights)
    {
        return WeightedChoiceIt(IteratorWrapper{values}, IteratorWrapper{weights});
    }

    template <typename ValueContainerT, typename WeightContainerT>
    [[nodiscard]] const auto& WeightedChoice(const ValueContainerT& values, const WeightContainerT& weights)
    {
        return WeightedChoiceIt(IteratorWrapper{values}, IteratorWrapper{weights});
    }

    template <typename ValueT, typename WeightT>
    [[nodiscard]] const ValueT& WeightedChoice(
        std::initializer_list<ValueT> valueInitList,
        std::initializer_list<WeightT> weightInitList
    )
    {
        return WeightedChoiceIt(
            IteratorWrapper{valueInitList.begin(), valueInitList.end()},
            IteratorWrapper{weightInitList.begin(), weightInitList.end()}
        );
    }

} // namespace zen::random
