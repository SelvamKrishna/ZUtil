#pragma once

#include "_export.hpp"

#include <vector>
#include <format>
#include <stdexcept>

namespace zen
{

    /// ---
    /// @brief ID-based storage container with binary-search lookup.
    /// Stores data elements associated with unique IDs in a contiguous buffer.
    /// Elements are stored in ascending order by ID, enabling logarithmic lookups.
    /// @tparam DataT Type of data stored in the buffer.
    /// ---
    template <typename DataT>
    struct ZEN_API FastAccessBuffer
    {
    private:
        /// @brief Internal structure binding an ID to stored data.
        struct _IdentifiedData
        {
            size_t id;   ///< Unique identifier
            DataT data;  ///< Stored value
        };

        std::vector<_IdentifiedData> _dataBuffer; ///< Sorted storage buffer
        std::vector<size_t> _freeIDs;             ///< Recycled IDs
        size_t _currentID = 0;                    ///< Next generated ID

        using DataRef  =       DataT&;
        using CDataRef = const DataT&;

        /// @brief Finds the iterator for the given ID.
        /// @param dataID ID to search for.
        /// @return Iterator pointing to the matching element.
        /// @throws std::out_of_range If the ID does not exist.
        /// @note O(log N)
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

        /// @brief Constructs the buffer with reserved capacity.
        /// @param reserveBuffer Initial capacity for the data buffer.
        explicit FastAccessBuffer(size_t reserveBuffer = 32) { this->_dataBuffer.reserve(reserveBuffer); }

        /// @brief Checks whether data with the given ID exists.
        /// @param dataID ID to check.
        /// @return True if the ID exists in the buffer.
        /// @note O(log N)
        [[nodiscard]] bool Contains(size_t dataID) const noexcept
        {
            try { auto _testIter = this->_GetDataIter(dataID); }
            catch (std::out_of_range) { return false; }
            return true;
        }

        /// @brief Inserts new data into the buffer.
        /// A unique ID is generated (or reused if available) and assigned to the data.
        /// @param data Data to insert.
        /// @return The unique ID associated with the inserted data.
        /// @note O(N)
        [[nodiscard]] size_t Insert(DataT&& data)
        {
            size_t id;

            if (!this->_freeIDs.empty())
            {
                id = this->_freeIDs.back();
                this->_freeIDs.pop_back();
            }
            else id = this->_currentID ++;

            auto insertPos = std::lower_bound(
                this->_dataBuffer.begin(), this->_dataBuffer.end(), id,
                [](const _IdentifiedData& lhs, size_t rhsID) { return lhs.id < rhsID; }
            );

            this->_dataBuffer.emplace(insertPos, _IdentifiedData{ id, std::move(data) });
            return id;
        }

        /// @brief Removes data associated with an ID.
        /// The removed ID is stored for reuse by future insertions.
        /// @param dataID ID of the element to remove.
        /// @throws std::out_of_range If the ID does not exist.
        /// @note O(N)
        void Remove(size_t dataID)
        {
            this->_dataBuffer.erase(this->_GetDataIter(dataID));
            this->_freeIDs.emplace_back(dataID);
        }

        /// @brief Returns the number of elements stored.
        /// @return Current size of the buffer.
        [[nodiscard]] size_t Size() const noexcept { return this->_dataBuffer.size(); }

        DataRef  operator [] (size_t dataID)       { return this->_GetDataIter(dataID)->data; }
        CDataRef operator [] (size_t dataID) const { return this->_GetDataIter(dataID)->data; }
    };

} // namespace zen
