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

template <typename Component>
class SparseArray
{
public:
    using value_type = std::optional<Component>;
    using reference_type = value_type &;
    using const_reference_type = value_type const &;
    using container_t = std::vector<value_type>;
    using size_type = typename container_t::size_type;
    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t ::const_iterator;

public:
    SparseArray() { _data.clear(); }
    SparseArray(SparseArray const &other) : _data(other._data) {}
    SparseArray(SparseArray &&other) noexcept : _data(std::move(other._data)) {}
    ~SparseArray() = default;
    SparseArray &operator=(SparseArray const &other)
    {
        for (auto &&i : other)
        {
            _data.insert(other);
        }
        return *this;
    }
    SparseArray &operator=(SparseArray &&other) noexcept
    {
        _data = std::move(other._data);
        return *this;
    }
    reference_type operator[](size_t idx)
    {
        return _data[idx];
    }
    const_reference_type operator[](size_t idx) const
    {
        return _data[idx];
    }
    iterator begin()
    {
        return _data.begin();
    }
    const_iterator begin() const
    {
        return _data.begin();
    }
    const_iterator cbegin() const
    {
        return _data.cbegin();
    }
    iterator end()
    {
        return _data.end();
    }
    const_iterator end() const
    {
        return _data.end();
    }
    const_iterator cend() const
    {
        return _data.cend();
    }
    size_type size() const
    {
        return _data.size();
    }
    reference_type insert_at(size_type pos, Component const &c)
    {
        try
        {
            if (pos >= _data.capacity())
                _data.resize(pos);
            _data.emplace(_data.begin() + pos, c);
        }
        catch (std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
        return _data[pos];
    }
    reference_type insert_at(size_type pos, Component &&c)
    {
        if (pos >= _data.capacity())
            _data.resize(pos + 1);
        _data.emplace(_data.begin() + pos, std::move(c));
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
    void erase(size_type pos)
    {
        _data[pos] = std::nullopt;
    }
    size_type get_index(value_type const &c) const
    {
        (void)c;
        throw std::runtime_error("Not implemented");
        // auto i = std::find(_data.begin(), _data.end(), c);
        // if (i == _data.end())
        //     throw std::runtime_error("Value not in SparseArray");
        // return i - _data.begin();
    }

private:
    container_t _data;
};

#endif /* !SPARSEARRAY_HPP_ */
