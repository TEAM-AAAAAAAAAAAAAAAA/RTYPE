#pragma once

#include <unordered_map>
#include <typeindex>
#include <any>
#include "SparseArray.hpp"

class Registry
{
public:
    template <class Component>
    SparseArray<Component> &register_component()
    {
        _components_arrays[std::type_index(typeid(Component))] = SparseArray<Component>();
        return get_components<Component>();
    }
    template <class Component>
    SparseArray<Component> &get_components()
    {
        return std::any_cast<SparseArray<Component>&>(_components_arrays.at(std::type_index(typeid(Component))));
    }

    template <class Component>
    SparseArray<Component> const &get_components() const
    {
        return std::any_cast<SparseArray<Component>>(_components_arrays.at(std::type_index(typeid(Component))));
    }

private:
    std::unordered_map<std::type_index, std::any> _components_arrays;
};
