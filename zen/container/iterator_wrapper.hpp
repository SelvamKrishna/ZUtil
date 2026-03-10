#pragma once

#include "../core/_export.hpp"

#include <stdexcept>
#include <algorithm>
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
            , _containerSize  {static_cast<size_t>(std::distance(_containerBegin, _containerEnd))}
        {
            if (_containerSize == 0) throw std::invalid_argument{"Iterator range is empty."};
        }

        template <typename ContainerT>
        IteratorWrapper(ContainerT& container) : IteratorWrapper {container.begin(), container.end()} {}

        template <typename ContainerT>
        IteratorWrapper(const ContainerT& container) : IteratorWrapper {container.begin(), container.end()} {}

        [[nodiscard]] constexpr size_t GetSize() const noexcept { return this->_containerSize; }

        [[nodiscard]] IteratorT GetBegin() const noexcept { return this->_containerBegin; }
        [[nodiscard]] IteratorT GetEnd()   const noexcept { return this->_containerEnd; }

        [[nodiscard]] reference operator[](size_t index) const
        {
            if (index >= this->GetSize()) throw std::out_of_range{"Index exceed size of range."};

            auto currentIt = this->_containerBegin;

            if constexpr (std::random_access_iterator<IteratorT>)
                return *(currentIt + static_cast<typename std::iterator_traits<IteratorT>::difference_type>(index));

            std::advance(currentIt, index);
            return *currentIt;
        }

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

    template <std::forward_iterator IteratorT>
    IteratorWrapper(IteratorT, IteratorT) -> IteratorWrapper<IteratorT>;

    template <typename ContainerT>
    IteratorWrapper(ContainerT&) -> IteratorWrapper<typename ContainerT::iterator>;

    template <typename ContainerT>
    IteratorWrapper(const ContainerT&) -> IteratorWrapper<typename ContainerT::const_iterator>;
} // namespace zen
