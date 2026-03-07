#pragma once

#include "_export.hpp"

#include <vector>
#include <format>
#include <stdexcept>

namespace zutil
{

    template<typename DataT>
    struct ZUTIL_API SparseSet
    {
    private:
        std::vector<size_t> _sparseIDs;
        std::vector<size_t> _denseIDs;
        std::vector<DataT>  _denseData;

        using DataRef  =       DataT&;
        using CDataRef = const DataT&;

    public:
        explicit SparseSet(size_t sparseReserve = 64, size_t denseReserve = 64)
        {
            this->_sparseIDs.reserve(sparseReserve);
            this->_denseIDs.reserve(denseReserve);
            this->_denseData.reserve(denseReserve);
        }

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

        [[nodiscard]] bool Contains(size_t dataID) const noexcept
        {
            if (dataID >= this->_sparseIDs.size()) return false;

            size_t index = this->_sparseIDs[dataID];
            return index < this->_denseIDs.size() && this->_denseIDs[index] == dataID;
        }

        const std::vector<DataT>& Dense() const noexcept { return this->_denseData; }

        [[nodiscard]] DataRef  At(size_t dataID)       { return this->_denseData[this->_sparseIDs[dataID]]; }
        [[nodiscard]] CDataRef At(size_t dataID) const { return this->_denseData[this->_sparseIDs[dataID]]; }

        [[nodiscard]] size_t Size() const noexcept { return this->_denseData.size(); }

        DataRef  operator [] (size_t dataID)       { return this->_denseData[this->_sparseIDs[dataID]]; }
        CDataRef operator [] (size_t dataID) const { return this->_denseData[this->_sparseIDs[dataID]]; }
    };

} // namespace zutil
