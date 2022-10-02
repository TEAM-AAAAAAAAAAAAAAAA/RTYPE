/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** SparseArray
*/

#ifndef SPARSEARRAY_HPP_
#define SPARSEARRAY_HPP_

#include <optional>
#include <vector>
#include <exception>
#include <iostream>

namespace ecs {

    /**
     * SparseArray class is the component container of the ecs. \n
     * This can be quite useful to store components that are defined for most entities,
     * because you don't have to store the entity ID alongside the component.
     * @tparam Component The type of component used as with template
     */
    template<typename Component>
    class SparseArray {
        public:
            using value_type = std::optional<Component>;
            using reference_type = value_type &;
            using const_reference_type = value_type const &;
            using container_t = std::vector<value_type>;
            using size_type = typename container_t::size_type;
            using iterator = typename container_t::iterator;
            using const_iterator = typename container_t::const_iterator;

        public:
            /**
             * Default constructor & destructor of the SparseArray class
             */
            SparseArray() { _data.clear(); }
            SparseArray(SparseArray const &other) : _data(other._data) {}
            SparseArray(SparseArray &&other) noexcept: _data(std::move(other._data)) {}
            ~SparseArray() = default;

            /**
             * Operator copy of the SparseArray class
             * @param other The SparseArray you want to copy
             * @return The Sparse array present in the class at the moment
             */
            SparseArray &operator=(SparseArray const &other) {
                for (auto &&i: other) {
                    _data.insert(other);
                }
                return *this;
            }

            /**
             * Operator move of the SparseArray class
             * @param other The SparseArray you want to move
             * @return The Sparse array present in the class at the moment
             */
            SparseArray &operator=(SparseArray &&other) noexcept {
                _data = std::move(other._data);
                return *this;
            }

            reference_type operator[](size_t idx) {
                return _data[idx];
            }

            const_reference_type operator[](size_t idx) const {
                return _data[idx];
            }

            iterator begin() {
                return _data.begin();
            }

            const_iterator begin() const {
                return _data.begin();
            }

            const_iterator cbegin() const {
                return _data.cbegin();
            }

            iterator end() {
                return _data.end();
            }

            const_iterator end() const {
                return _data.end();
            }

            const_iterator cend() const {
                return _data.cend();
            }

            size_type size() const {
                return _data.size();
            }

            reference_type insert_at(size_type pos, Component const &c) {
                try {
                    if (pos >= _data.capacity())
                        _data.resize(pos);
                    _data.emplace(_data.begin() + pos, c);
                }
                catch (std::exception &e) {
                    std::cout << e.what() << std::endl;
                }
                return _data[pos];
            }

            reference_type insert_at(size_type pos, Component &&c) {
                try {
                    if (pos >= _data.capacity())
                        _data.resize(pos + 1);
                    _data.emplace(_data.begin() + pos, std::move(c));
                }
                catch (std::exception &e) {
                    std::cout << e.what() << std::endl;
                }
                return _data[pos];
            }

            template <class... Params>
            reference_type emplace_at(size_type pos, Params &&...args)
            {
                if (pos >= _data.capacity())
                    _data.resize(pos + 1);
                _data.emplace(_data.begin() + pos, Component(args...));
                return _data[pos];
            }

            void erase(size_type pos) {
                _data[pos] = std::nullopt;
            }

            /**
             * This function is used to get the index of the std::optional<Component> of the std::vector<std::optional<Component>> _data according to the given value_type (std::optional<Component>)
             * @param c The std::optional<Component>, type of the component you want the index
             * @return The size_type of the value_type's index you are looking for
             */
            size_type get_index(value_type const &c) const {
                if (!c.has_value())
                    return std::nullopt;
                for (auto iterator =  _data.begin(); iterator != _data.end(); iterator++)
                    if (iterator.has_value() && iterator.value() == c.value()) {
                        return iterator.value();
                    }
                return std::nullopt;
            }

        private:
            /**
             * Private member _data represented by a std::vector<std::optional<Component>> the data of the component
             */
            container_t _data;
    };
}

#endif /* !SPARSEARRAY_HPP_ */
