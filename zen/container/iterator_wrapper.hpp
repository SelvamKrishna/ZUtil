#pragma once

#include "../core/_export.hpp"

#include <stdexcept>
#include <algorithm>
#include <iterator>

namespace zen::container {

    /// ---
    /// @brief Lightweight wrapper around an iterator range.
    /// Provides a simple abstraction over a pair of iterators,
    /// Designed primarily for internal utilities
    /// @tparam IteratorT Iterator type satisfying std::forward_iterator.
    /// ---
    template <std::forward_iterator IteratorT>
    struct ZEN_API IteratorWrapper {
    private:
        IteratorT _containerBegin; ///< Beginning iterator of the wrapped range.
        IteratorT _containerEnd;   ///< End iterator of the wrapped range.
        size_t    _containerSize;  ///< Cached size of the iterator range.

    public:
        /// Iterator category of the wrapped iterator type.
        using iterator_category = typename std::iterator_traits<IteratorT>::iterator_category;

        /// Value type stored in the iterator range.
        using value_type = typename std::iterator_traits<IteratorT>::value_type;

        /// Difference type of the iterator.
        using difference_type = typename std::iterator_traits<IteratorT>::difference_type;

        /// Pointer type of the iterator.
        using pointer = typename std::iterator_traits<IteratorT>::pointer;

        /// Reference type of the iterator.
        using reference = typename std::iterator_traits<IteratorT>::reference;

        /// @brief Constructs a wrapper from an iterator pair.
        /// @param itBegin Beginning iterator of the range.
        /// @param itEnd End iterator of the range.
        /// @throws std::invalid_argument if the iterator range is empty.
        IteratorWrapper(IteratorT itBegin, IteratorT itEnd)
            : _containerBegin {std::move(itBegin)}
            , _containerEnd   {std::move(itEnd)}
            , _containerSize  {static_cast<size_t>(std::distance(_containerBegin, _containerEnd))}
        {
            if (_containerSize == 0) throw std::invalid_argument{"Iterator range is empty."};
        }

        /// @brief Constructs a wrapper from a mutable container.
        /// @tparam ContainerT Container type providing begin/end iterators.
        /// @param container Container to wrap.
        template <typename ContainerT>
        IteratorWrapper(ContainerT& container) : IteratorWrapper {container.begin(), container.end()} {}

        /// @brief Constructs a wrapper from a const container.
        /// @tparam ContainerT Container type providing const iterators.
        /// @param container Const container to wrap.
        template <typename ContainerT>
        IteratorWrapper(const ContainerT& container) : IteratorWrapper {container.begin(), container.end()} {}

        /// @brief Returns the number of elements in the iterator range.
        /// @return Size of the wrapped range.
        [[nodiscard]] constexpr size_t GetSize() const noexcept { return this->_containerSize; }

        /// @brief Returns the beginning iterator of the range.
        [[nodiscard]] IteratorT GetBegin() const noexcept { return this->_containerBegin; }

        /// @brief Returns the end iterator of the range.
        [[nodiscard]] IteratorT GetEnd() const noexcept { return this->_containerEnd; }

        /// @brief Accesses an element at the specified index.
        /// @param index Index within the range.
        /// @return Reference to the element at the given index.
        /// @throws std::out_of_range if the index exceeds the range size.
        [[nodiscard]] reference operator[](size_t index) const
        {
            if (index >= this->GetSize()) throw std::out_of_range{"Index exceed size of range."};

            auto currentIt = this->_containerBegin;

            if constexpr (std::random_access_iterator<IteratorT>) return *(
                currentIt +
                static_cast<typename std::iterator_traits<IteratorT>::difference_type>(index)
            );

            std::advance(currentIt, index);
            return *currentIt;
        }

        /// @brief Compares two iterator wrappers for equality.
        /// @param other Wrapper to compare against.
        [[nodiscard]] bool operator==(const IteratorWrapper& other) const noexcept
        {
            return this->_containerBegin == other._containerBegin && this->_containerEnd == other._containerEnd;
        }

        /// @brief Compares two iterator wrappers for inequality.
        /// @param other Wrapper to compare against.
        [[nodiscard]] bool operator!=(const IteratorWrapper& other) const noexcept
        {
            return this->_containerBegin != other._containerBegin || this->_containerEnd != other._containerEnd;
        }

        /// @brief Returns the beginning iterator.
        [[nodiscard]] IteratorT begin() const noexcept { return this->_containerBegin; }

        /// @brief Returns the end iterator.
        [[nodiscard]] IteratorT end() const noexcept { return this->_containerEnd; }
    };

    /// @brief Class template argument deduction guide for iterator pairs.
    template <std::forward_iterator IteratorT>
    IteratorWrapper(IteratorT, IteratorT) -> IteratorWrapper<IteratorT>;

    /// @brief Deduction guide for mutable containers.
    template <typename ContainerT>
    IteratorWrapper(ContainerT&) -> IteratorWrapper<typename ContainerT::iterator>;

    /// @brief Deduction guide for const containers.
    template <typename ContainerT>
    IteratorWrapper(const ContainerT&) -> IteratorWrapper<typename ContainerT::const_iterator>;

} // namespace zen::container
