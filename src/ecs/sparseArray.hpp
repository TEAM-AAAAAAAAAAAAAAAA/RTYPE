/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** sparseArray
*/

#ifndef SPARSEARRAY_HPP_
#define SPARSEARRAY_HPP_

#include <optional>
#include <vector>

template <typename Component> // You can also mirror the definition of std :: vector , that takes an additional allocator.
class sparse_array
{
public:
    using value_type = std::optional<Component>; // optional component type
    using reference_type = value_type &;
    using const_reference_type = value_type const &;
    using container_t = std::vector<value_type>; // optionally add your allocator template here.
    using size_type = typename container_t::size_type;
    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t ::const_iterator;

public:
    sparse_array() { _data.clear(); }                                 // You can add more constructors.
    sparse_array(sparse_array const &other) : _data(other._data) {}     // copy constructor
    sparse_array(sparse_array &&other) noexcept : _data(other._data) {} // move constructor
    ~sparse_array() = default;
    sparse_array &operator=(sparse_array const &other)
    {
        for (auto &&i : other)
        {
            _data.insert(other);
        }
        return *this;
    }
    sparse_array &operator=(sparse_array &&other) noexcept
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
                _data.resize(pos + 1);
            _data.emplace(_data.begin() + pos, c);
        }
        catch (std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
        return _data.at(pos);
    }
    reference_type insert_at(size_type pos, Component &&c)
    {
        try
        {
            if (pos >= _data.capacity())
                _data.resize(pos + 1);
            _data.emplace(_data.begin() + pos, std::move(c));
        }
        catch (std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
        return _data.at(pos);
    }
    template <class... Params>
    reference_type emplace_at(size_type pos, Params &&...)
    {}
    void erase(size_type pos)
    {
        _data[pos] = std::nullopt;
    }
    size_type get_index(value_type const &) const
    {}

private:
    container_t _data;
};

#endif /* !SPARSEARRAY_HPP_ */
