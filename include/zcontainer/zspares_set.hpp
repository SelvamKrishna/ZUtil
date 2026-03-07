#pragma once

#include "_export.hpp"

#include <vector>
#include <format>
#include <stdexcept>

namespace zutil
{

    /// ---
    /// @brief Sparse set container providing O(1) insertion, removal, and lookup by ID.
    /// Stores elements in a dense array while maintaining a sparse lookup table that
    /// maps external IDs to dense indices. commonly used in Entity Component Systems (ECS)
    /// where entities are sparse but components must be iterated efficiently.
    /// @tparam DataT Type of data stored in the sparse set.
    /// ---
    template<typename DataT>
    struct ZUTIL_API SparseSet
    {
    private:
        std::vector<size_t> _sparseIDs; ///< Maps external IDs → dense indices
        std::vector<size_t> _denseIDs;  ///< Maps dense indices → external IDs
        std::vector<DataT>  _denseData; ///< Contiguous storage of data

        using DataRef  =       DataT&;
        using CDataRef = const DataT&;

    public:
        /// @brief Constructs a sparse set with reserved capacity.
        /// @param sparseReserve Initial capacity for the sparse ID lookup table.
        /// @param denseReserve  Initial capacity for dense storage.
        explicit SparseSet(size_t sparseReserve = 64, size_t denseReserve = 64)
        {
            this->_sparseIDs.reserve(sparseReserve);
            this->_denseIDs.reserve(denseReserve);
            this->_denseData.reserve(denseReserve);
        }

        /// @brief Inserts a value associated with an ID.
        /// @param id External ID associated with the value.
        /// @param value Data to store.
        /// @throws std::invalid_argument If the ID already exists.
        /// @note θ(1), O(N)
        void Insert(size_t id, DataT value)
        {
            if (this->Contains(id)) throw std::invalid_argument {
                std::format("Data with ID {}, already exists.", id)
            };

            if (id >= this->_sparseIDs.size()) this->_sparseIDs.resize(id + 1);

            this->_sparseIDs[id] = this->_denseIDs.size();
            this->_denseIDs.push_back(id);
            this->_denseData.push_back(std::move(value));
        }

        /// @brief Removes the value associated with an ID.
        /// @param dataID ID of the element to remove.
        /// @throws std::invalid_argument If the ID does not exist.
        /// @note O(1)
        void Remove(size_t dataID)
        {
            if (!this->Contains(dataID)) throw std::invalid_argument {
                std::format("Data with ID {}, doesn't exists.", dataID)
            };

            size_t index     = this->_sparseIDs[dataID];
            size_t lastIndex = this->_denseIDs.size() - 1;
            size_t lastID    = this->_denseIDs[lastIndex];

            this->_denseIDs[index]  = lastID;
            this->_denseData[index] = std::move(this->_denseData[lastIndex]);

            this->_sparseIDs[lastID] = index;
            this->_denseIDs.pop_back();
            this->_denseData.pop_back();
        }

        /// @brief Checks whether an ID exists in the sparse set.
        /// @param dataID ID to check.
        /// @return True if the ID is present.
        /// @note O(1)
        [[nodiscard]] bool Contains(size_t dataID) const noexcept
        {
            if (dataID >= this->_sparseIDs.size()) return false;

            size_t index = this->_sparseIDs[dataID];
            return index < this->_denseIDs.size() && this->_denseIDs[index] == dataID;
        }

        /// @brief Returns the dense storage buffer.
        /// Useful for fast iteration over all stored elements.
        /// @return Const reference to the dense data vector.
        const std::vector<DataT>& Dense() const noexcept { return this->_denseData; }

        /// @brief Returns the number of stored elements.
        /// @return Current number of elements in the dense storage.
        [[nodiscard]] constexpr size_t Size() const noexcept { return this->_denseData.size(); }

        DataRef  operator [] (size_t dataID)       { return this->_denseData[this->_sparseIDs[dataID]]; }
        CDataRef operator [] (size_t dataID) const { return this->_denseData[this->_sparseIDs[dataID]]; }
    };

} // namespace zutil
