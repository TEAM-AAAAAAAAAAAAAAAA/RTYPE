#pragma once

#include <unordered_map>
#include <typeindex>
#include <any>
#include <functional>
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

        std::function<void(Registry&, Entity const&)> erase_func = [] (Registry &r, Entity const& e) {
            SparseArray<Component>& array = r.template get_components<Component>();
            array.erase(e);
        };
        _erase_functions.push_back(erase_func);
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
        if (_entity_recycle_bin.empty())
        {
            _last_entity++;
            return Entity(_last_entity - 1);
        }
        size_t id = _entity_recycle_bin.top();
        _entity_recycle_bin.pop();
        return Entity(id);
    }

    Entity entity_from_index(std ::size_t idx)
    {
        // if (idx < _last_entity && 
    } // ?

    void kill_entity(Entity const &e)
    {
        for (const auto& erase_func: _erase_functions)
            erase_func(*this, e);
        _entity_recycle_bin.push(e);
    }

    template <typename Component>
    typename SparseArray<Component>::reference_type add_component(Entity const &to, Component &&c)
    {
        return std::any_cast<SparseArray<Component>&>(_components_arrays[std::type_index(typeid(Component))]).insert_at(to, c);
    }

    template <typename Component, typename... Params>
    typename SparseArray<Component>::reference_type emplace_component(Entity const &to, Params &&...p)
    {
        return std::any_cast<SparseArray<Component>&>(_components_arrays[std::type_index(typeid(Component))]).insert_at(to, Component(p...));
    }

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
    std::vector<std::function<void(Registry &, Entity const &)>> _erase_functions;
    std::stack<size_t> _entity_recycle_bin;
    size_t _last_entity;
};
