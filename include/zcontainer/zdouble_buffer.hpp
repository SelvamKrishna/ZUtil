#pragma once

#include "_export.hpp"

#include <array>

namespace zutil
{

    // ---
    // Stores 2 seperate items, and provided proper Read & Write access.
    // ---
    template<typename DataT>
    struct ZUTIL_API DoubleBuffer
    {
    private:
        std::array<DataT, 2> _buffers;
        size_t _readIndex  = 0;
        size_t _writeIndex = 1;

        using WBufferRef =       DataT&;
        using RBufferRef = const DataT&;

    public:
        explicit DoubleBuffer(DataT readValue = {}, DataT writeValue = {})
        {
            this->_buffers[this->_readIndex]  = std::move(readValue);
            this->_buffers[this->_writeIndex] = std::move(writeValue);
        }

        // --- Returns the Read Buffer : O(1) ---
        [[nodiscard]] RBufferRef Read() const noexcept { return this->_buffers[this->_readIndex]; }

        // --- Returns the Write Buffer : O(1) ---
        [[nodiscard]] WBufferRef Write()      noexcept { return this->_buffers[this->_writeIndex]; }

        // --- Swap's the read and write buffers : O(1) ---
        void Swap() noexcept { std::swap(this->_readIndex, this->_writeIndex); }
    };

} // namespace zutil
