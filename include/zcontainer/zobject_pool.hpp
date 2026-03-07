#pragma once

#include "_export.hpp"

#include <vector>
#include <format>
#include <stdexcept>

namespace zutil
{

    // ---
    // ---
    template<typename DataT>
    struct ZUTIL_API ObjectPool
    {
    private:
        std::vector<DataT> _objectBuffer;
        std::vector<bool>  _objectActive;

        const size_t POOL_SIZE;

    public:
        explicit ObjectPool(size_t poolReserve = 64)
            : POOL_SIZE {poolReserve}
        {
            this->_objectBuffer.resize(poolReserve);
            this->_objectActive.resize(poolReserve);
        }

        template <typename... Args>
        [[nodiscard]] DataT& Acquire(Args&&... args)
        {
            for (size_t idx = 0; idx < this->POOL_SIZE; ++ idx)
            {
                if (!this->_objectActive[idx])
                {
                    this->_objectActive[idx] = true;
                    this->_objectBuffer[idx] = DataT {std::forward<Args>(args)...};
                    return this->_objectBuffer[idx];
                }
            }

            throw std::overflow_error { std::format("ObjectPool exhausted. Provided limit {}", this->POOL_SIZE) };
        }

        void Release(DataT* objectPtr)
        {
            for (size_t idx = 0; idx < this->POOL_SIZE; ++ idx)
            {
                if(objectPtr == &this->_objectBuffer[idx])
                {
                    this->_objectActive[idx] = false;
                    return;
                }
            }
        }

        template <typename Fn>
        void ForEachActive(Fn fn)
        {
            for (size_t idx = 0; idx < this->POOL_SIZE; ++ idx)
            {
                if (this->_objectActive[idx]) fn(this->_objectBuffer[idx]);
            }
        }
    };

} // namespace zutil
