#pragma once

#include "_export.hpp"

#include <vector>
#include <format>
#include <stdexcept>

namespace zutil
{

    // ---
    // Stores items and provides fast accessing
    // Note: Insertion and Deletion are O(n) operations
    // ---
    template <typename DataT>
    struct ZUTIL_API FastAccessBuffer
    {
    private:
        struct _IdentifiedData { size_t id; DataT data; };

        std::vector<_IdentifiedData> _dataBuffer;
        size_t _currentID = 0;

        using DataRef  =       DataT&;
        using CDataRef = const DataT&;

        std::vector<_IdentifiedData>::iterator _GetDataIter(size_t dataID)
        {
            auto it = std::lower_bound(
                this->_dataBuffer.begin(), this->_dataBuffer.end(), dataID,
                [](const _IdentifiedData& lhsData, size_t rhsID) { return lhsData.id < rhsID; }
            );

            if (it == this->_dataBuffer.end() || it->id != dataID) throw std::out_of_range {
                std::format("Can't find Data with ID {}.", dataID)
            };

            return it;
        }

    public:
        explicit FastAccessBuffer(size_t reserveBuffer = 32) { this->_dataBuffer.reserve(reserveBuffer); }

        // --- Add data to the buffer ---
        // RETURNS: the unique ID of the loaded data
        [[nodiscard]] size_t Insert(DataT&& data)
        {
            size_t id = this->_currentID++;
            this->_dataBuffer.emplace_back(_IdentifiedData {id, std::move(data)});
            return id;
        }

        // --- Remove data from the buffer using it's id ---
        void Remove(size_t dataID) { this->_dataBuffer.erase(this->_GetDataIter(dataID)); }

        [[nodiscard]] DataRef  At(size_t dataID)       { return this->_GetDataIter(dataID)->data; }
        [[nodiscard]] CDataRef At(size_t dataID) const { return this->_GetDataIter(dataID)->data; }

        [[nodiscard]] size_t Size() const noexcept { return this->_dataBuffer.size(); }

        DataRef  operator [] (size_t dataID)       { return this->_GetDataIter(dataID); }
        CDataRef operator [] (size_t dataID) const { return this->_GetDataIter(dataID); }
    };

} // namespace zutil
