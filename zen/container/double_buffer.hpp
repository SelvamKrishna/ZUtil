#pragma once

#include "../core/_export.hpp"

#include <array>

namespace zen
{

    /// ---
    /// @brief Double-buffered storage container.
    /// Maintains two instances of a data object: a read buffer and a write buffer.
    /// The read buffer represents the currently visible state, while the write
    /// buffer can be safely modified. Calling Swap() exchanges the two buffers.
    /// @tparam DataT Type of data stored in the buffers.
    /// ---
    template<typename DataT>
    struct ZEN_API DoubleBuffer
    {
    private:
        std::array<DataT, 2> _buffers; ///< Internal storage for the two buffers

        size_t _readIndex  = 0; ///< Index of the buffer used for reading
        size_t _writeIndex = 1; ///< Index of the buffer used for writing

        using WBufferRef =       DataT&;
        using RBufferRef = const DataT&;

    public:
        /// @brief Constructs the double buffer with initial values.
        /// @param readValue  Initial value for the read buffer.
        /// @param writeValue Initial value for the write buffer.
        explicit DoubleBuffer(DataT readValue = {}, DataT writeValue = {})
        {
            this->_buffers[this->_readIndex]  = std::move(readValue);
            this->_buffers[this->_writeIndex] = std::move(writeValue);
        }

        /// @brief Returns the current read buffer.
        /// @return Const reference to the read buffer.
        /// @note O(1)
        [[nodiscard]] RBufferRef Read() const noexcept { return this->_buffers[this->_readIndex]; }

        /// @brief Returns the current write buffer.
        /// @return Reference to the write buffer.
        /// @note O(1)
        [[nodiscard]] WBufferRef Write() noexcept { return this->_buffers[this->_writeIndex]; }

        /// @brief Swaps the read and write buffers.
        /// @note O(1)
        void Swap() noexcept
        {
            std::swap(this->_readIndex, this->_writeIndex);
            this->_buffers[this->_writeIndex] = {};
        }
    };

} // namespace zen
