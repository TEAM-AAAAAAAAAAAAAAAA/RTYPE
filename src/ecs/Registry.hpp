#pragma once

#include <unordered_map>
#include <typeindex>
#include <any>
#include "SparseArray.hpp"
#include "Entity.hpp"
#include <stack>
#include <exception>
#include <iostream>

class Registry
{
public:
    Registry() : _last_entity(0) {}

    template <class Component>
    SparseArray<Component> &register_component()
    {
        _components_arrays[std::type_index(typeid(Component))] = SparseArray<Component>();
        return get_components<Component>();
    }
    template <class Component>
    SparseArray<Component> &get_components()
    {
        return std::any_cast<SparseArray<Component> &>(_components_arrays.at(std::type_index(typeid(Component))));
    }

    template <class Component>
    SparseArray<Component> const &get_components() const
    {
        return std::any_cast<SparseArray<Component>>(_components_arrays.at(std::type_index(typeid(Component))));
    }

    Entity spawn_entity()
    {
        if (_entity_recycle_bin.size() == 0)
        {
            _last_entity++;
            return Entity(_last_entity - 1);
        }
        size_t id = _entity_recycle_bin.top();
        _entity_recycle_bin.pop();
        return Entity(id);
    }

    Entity entity_from_index(std ::size_t idx); // ?

    void kill_entity(Entity const &e)
    {
        for (auto &&i : _components_arrays)
        {
            std::any_cast<SparseArray<std::any>>(i.second)[e] = std::nullopt;
        }
        _entity_recycle_bin.push(e);
    }

    template <typename Component>
    typename SparseArray<Component>::reference_type add_component(Entity const &to, Component &&c)
    {
        return std::any_cast<SparseArray<Component>&>(_components_arrays[std::type_index(typeid(Component))]).insert_at(to, c);
    }

    template <typename Component, typename... Params>
    typename SparseArray<Component>::reference_type emplace_component(Entity const &to, Params &&...p);

    template <typename Component>
    void remove_component(Entity const &from)
    {
        try
        {
            std::any_cast<SparseArray<Component>&>(_components_arrays.at(std::type_index(typeid(Component))))[from] = std::nullopt;
        }
        catch (std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
    }

private:
    std::unordered_map<std::type_index, std::any> _components_arrays;
    std::stack<size_t> _entity_recycle_bin;
    size_t _last_entity;
};
