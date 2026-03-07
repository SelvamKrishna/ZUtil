#pragma once

#include "_export.hpp"

#include <vector>

namespace zutil
{

    /// ---
    /// @brief Fixed-size object pool.
    /// Stores objects in a preallocated buffer and tracks active slots using a bitmap.
    /// @tparam DataT Type stored in the pool.
    /// ---
    template<typename DataT>
    struct ZUTIL_API ObjectPool
    {
    private:
        std::vector<DataT> _objectBuffer; ///< Densely packed buffer of data
        std::vector<bool>  _objectActive; ///< Active flags of all data by index
        size_t _currentlyActive = 0;      ///< No.of active objects

    public:
        /// @param poolReserve Fixed capacity of the pool
        explicit ObjectPool(size_t poolReserve = 64)
        {
            this->_objectBuffer.resize(poolReserve);
            this->_objectActive.resize(poolReserve, false);
        }

        /// @brief Acquire an object from the pool
        /// @param args Arguments used to initialize the object
        /// @return Pointer to the object, or nullptr if the pool is full
        template <typename... Args>
        [[nodiscard]] DataT* Acquire(Args&&... args)
        {
            for (size_t idx = 0; idx < this->_objectBuffer.size(); ++ idx)
            {
                if (this->_objectActive[idx] == false)
                {
                    this->_objectActive[idx] = true;
                    this->_currentlyActive ++;

                    this->_objectBuffer[idx] = DataT {std::forward<Args>(args)...};
                    return &this->_objectBuffer[idx];
                }
            }

            return nullptr;
        }

        /// @brief Release an object back to the pool
        /// @param objectPtr Pointer previously returned by Acquire
        /// @note objectPtr must belong to this pool
        void Release(DataT* objectPtr)
        {
            size_t idx = objectPtr - this->_objectBuffer.data();
            this->_objectActive[idx] = false;
            this->_currentlyActive --;
        }

        /// @brief Iterate over all active objects in the pool
        /// @param fn Callable invoked for each active objects
        /// @note fn must match `void (Data&)` signature
        template <typename Fn>
        void ForEachActive(Fn fn)
        {
            for (size_t idx = 0; idx < this->_objectBuffer.size(); ++ idx)
            {
                if (this->_objectActive[idx] == true) fn(this->_objectBuffer[idx]);
            }
        }

        /// @brief Check whether the pool has reached capacity
        /// @return True if no more objects can be acquired
        [[nodiscard]] constexpr bool IsFull() const noexcept { return this->_currentlyActive == this->_objectBuffer.size(); }
    };

} // namespace zutil
