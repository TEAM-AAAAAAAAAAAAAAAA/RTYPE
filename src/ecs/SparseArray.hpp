/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** SparseArray
*/

#pragma once

#include <exception>
#include <iostream>
#include <optional>
#include <vector>
#include "Constant.hpp"

namespace ecs
{
    /**
     * SparseArray class is the component container of the ecs. \n
     * This can be quite useful to store components that are defined for most entities,
     * because you don't have to store the entity ID alongside the component.
     * @tparam Component The type of component used as with template
     */
    template <typename Component> class SparseArray {
      public:
        using valueType = std::optional<Component>;
        using referenceType = valueType &;
        using constReferenceType = valueType const &;
        using container = std::vector<valueType>;
        using sizeType = typename container::size_type;
        using iterator = typename container::iterator;
        using constIterator = typename container::const_iterator;

      public:
        /**
         * Default constructor & destructor of the SparseArray class
         */
        SparseArray() { _data.clear(); }
        SparseArray(SparseArray const &other) : _data(other._data) {}
        SparseArray(SparseArray &&other) noexcept : _data(std::move(other._data)) {}
        ~SparseArray() = default;

        /**
         * Operator copy of the SparseArray class
         * @param other The SparseArray you want to copy
         * @return The Sparse array present in the class at the moment
         */
        SparseArray &operator=(SparseArray const &other)
        {
            for (auto &&i : other) {
                _data.insert(other);
            }
            return *this;
        }

        /**
         * Operator move of the SparseArray class
         * @param other The SparseArray you want to move
         * @return The Sparse array present in the class at the moment
         */
        SparseArray &operator=(SparseArray &&other) noexcept
        {
            _data = std::move(other._data);
            return *this;
        }

        referenceType operator[](size_t idx) { return _data[idx]; }

        constReferenceType operator[](size_t idx) const { return _data[idx]; }

        iterator begin() { return _data.begin(); }

        constIterator begin() const { return _data.begin(); }

        constIterator cBegin() const { return _data.cbegin(); }

        iterator end() { return _data.end(); }

        constIterator end() const { return _data.end(); }

        constIterator cEnd() const { return _data.cend(); }

        sizeType size() const { return _data.size(); }

        referenceType insertAt(sizeType pos, Component const &c)
        {
            if (pos >= _data.size())
                _data.resize(pos + 1, std::nullopt);
            _data.at(pos) = c;
            return _data[pos];
        }

        referenceType insertAt(sizeType pos, Component &&c)
        {
            if (pos >= _data.size())
                _data.resize(pos + 1, std::nullopt);
            _data.at(pos) = c;
            return _data[pos];
        }

        template <class... Params> referenceType emplaceAt(sizeType pos, Params &&...args)
        {
            if (pos >= _data.size())
                _data.resize(pos + 1, std::nullopt);
            _data.at(pos) = Component(args...);
            return _data[pos];
        }

        void erase(sizeType pos)
        {
            if (pos < _data.size())
                if (_data[pos])
                    _data[pos] = std::nullopt;
        }

        /**
         * This function is used to get the index of the std::optional<Component> of the
         * std::vector<std::optional<Component>> _data according to the given valueType (std::optional<Component>)
         * @param c The std::optional<Component>, type of the component you want the index
         * @return The sizeType of the valueType's index you are looking for
         */
        sizeType getIndex(valueType const &c) const
        {
            std::size_t cpt = 0;
            if (!c.has_value())
                return utils::constant::npos;
            for (valueType iterator = _data.begin(); iterator != _data.end(); iterator++, cpt++)
                if (iterator.has_value() && iterator.value() == c.value()) {
                    return cpt;
                }
            return utils::constant::npos;
        }

      private:
        /**
         * Private member _data represented by a std::vector<std::optional<Component>> the data of the component
         */
        container _data;
    };
} // namespace ecs
