#pragma once

#include "../core/_export.hpp"

#include <stdexcept>
#include <iterator>

namespace zen
{

    template <std::forward_iterator IteratorT>
    struct ZEN_API IteratorWrapper {
    private:
        IteratorT _containerBegin;
        IteratorT _containerEnd;
        size_t    _containerSize;

    public:
        using iterator_category = typename std::iterator_traits<IteratorT>::iterator_category;
        using value_type        = typename std::iterator_traits<IteratorT>::value_type;
        using difference_type   = typename std::iterator_traits<IteratorT>::difference_type;
        using pointer           = typename std::iterator_traits<IteratorT>::pointer;
        using reference         = typename std::iterator_traits<IteratorT>::reference;

        IteratorWrapper(IteratorT itBegin, IteratorT itEnd)
            : _containerBegin {std::move(itBegin)}
            , _containerEnd   {std::move(itEnd)}
            , _containerSize  {std::distance(_containerBegin, _containerEnd)}
        {
            if (_containerSize == 0) throw std::invalid_argument{"Iterator range is empty."};
        }

        template <typename ContainerT>
        explicit IteratorWrapper(ContainerT& container) : IteratorWrapper(container.begin(), container.end()) {}

        template <typename ContainerT>
        explicit IteratorWrapper(const ContainerT& container) : IteratorWrapper(container.begin(), container.end()) {}

        [[nodiscard]] constexpr size_t GetSize() const noexcept { return this->_containerSize; }

        [[nodiscard]] IteratorT GetBegin() const noexcept { return this->_containerBegin; }
        [[nodiscard]] IteratorT GetEnd()   const noexcept { return this->_containerEnd; }

        [[nodiscard]] IteratorT Advance(size_t steps) const
        {
            if (steps >= this->GetSize()) throw std::out_of_range{"Advance steps exceed range."};

            if constexpr (std::random_access_iterator<IteratorT>) return this->_containerBegin + steps;

            auto currentIt = this->_containerBegin;
            std::advance(currentIt, steps);
            return currentIt;
        }

        [[nodiscard]] IteratorT operator[](size_t index) const { return this->Advance(index); }

        [[nodiscard]] bool operator==(const IteratorWrapper& other) const noexcept
        {
            return this->_containerBegin == other._containerBegin && this->_containerEnd == other._containerEnd;
        }

        [[nodiscard]] bool operator!=(const IteratorWrapper& other) const noexcept
        {
            return this->_containerBegin != other._containerBegin || this->_containerEnd != other._containerEnd;
        }

        [[nodiscard]] IteratorT begin() const noexcept { return this->_containerBegin; }
        [[nodiscard]] IteratorT end()   const noexcept { return this->_containerEnd; }
    };
} // namespace zen
