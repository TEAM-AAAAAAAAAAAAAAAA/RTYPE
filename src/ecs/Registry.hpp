#pragma once

#include <any>
#include <exception>
#include <functional>
#include <iostream>
#include <typeindex>
#include "Constant.hpp"
#include "Entity.hpp"
#include "SparseArray.hpp"
#include <unordered_map>

namespace ecs
{
    /**
     * [This is the core of the ECS] \n
     * This class contains many feature as follows : \n
     * - Component Manager, Registry is able to register/get components from the unordered map\n
     * - Entity Manager, Registry is able to create/delete and add component to an Entity\n
     *      (Feel free to check the Entity.hpp to learn more about the subject)\n
     * - EntitiesBin Manager, Registry is saving killed entity in the bin that which can be
     * recovered instead of creating another one\n
     */
    class Registry {
      public:
        Registry() : _lastEntity(0) {}

        /**
         * This function is used to register a new component in the private member _unordered_map
         * @tparam Component The type of components you want to register
         * @return The SparseArray of components you just registered
         */
        template <class Component> SparseArray<Component> &registerComponent()
        {
            if (_componentsArrays.find(std::type_index(typeid(Component))) != _componentsArrays.end())
                return getComponents<Component>();
            _componentsArrays[std::type_index(typeid(Component))] = SparseArray<Component>();

            std::function<void(Registry &, Entity const &)> erase_func = [](Registry &r, Entity const &e) {
                SparseArray<Component> &array = r.getComponents<Component>();
                if (e._id > array.size())
                    return;
                array.erase(e._id);
            };
            _eraseFunctions.push_back(erase_func);
            return getComponents<Component>();
        }

        /**
         * This function is used to get all components already registered in the Registry class
         * following the given component template
         * @tparam Component The type of components you want to get
         * @return The SparseArray of components you asked
         */
        template <class Component> SparseArray<Component> &getComponents()
        {
            return std::any_cast<SparseArray<Component> &>(_componentsArrays.at(std::type_index(typeid(Component))));
        }

        /**
         * This function is used to get all components already registered in the Registry class
         * following the given component template as const
         * @tparam Component The type of components you want to get
         * @return The const SparseArray of components you asked
         */
        template <class Component> SparseArray<Component> const &getComponents() const
        {
            return std::any_cast<SparseArray<Component>>(_componentsArrays.at(std::type_index(typeid(Component))));
        }

        /**
         * This function is used to create a new entity if it doesn't exists in the _entitiesBin,
         * otherwise it recover it from the bin
         * @return The entity just created (id)
         */
        Entity spawn_entity()
        {
            size_t front;

            if (_entitiesBin.empty()) {
                _lastEntity++;
                return Entity(_lastEntity - 1);
            }
            front = _entitiesBin.front();
            _entitiesBin.erase(_entitiesBin.begin());
            return Entity(front);
        }

        /**
         * This function is used to get the id of the Entity following the give index
         * @param idx The index of the entity whose id is desired
         * @return The id of the Entity if it exists, ecs::npos otherwise
         */
        Entity entityFromIndex(std::size_t idx)
        {
            if (idx >= _lastEntity) {
                std::cerr << "Error with entity " << idx << "(" << _lastEntity << " max)" << std::endl;
            }
            return Entity(idx);
        }

        /**
         * This is used to delete the given Entity (id)
         * For optimisation purposes, Registry class push it in the _entitiesBin
         * @param e The Entity you want to kill
         */
        void killEntity(Entity const &e)
        {
            if (e._id == utils::constant::npos)
                return;
            for (const auto &eraseFunc : _eraseFunctions)
                eraseFunc(*this, e);
            _entitiesBin.push_back(e._id);
        }

        /**
         * This function is used to add a component into the Entity given as parameter.
         * In the same time, the erase function of this component is pushed into the _eraseFunctions vector,
         * in this case we can simply delete a component without needing type of it
         * @tparam Component The type of component want to be added
         * @param to The Entity in which you want to add component
         * @param c The component you want to add
         * @return the SparseArray<Component> reference of the component
         */
        template <typename Component>
        typename SparseArray<Component>::referenceType addComponent(Entity const &to, Component &&c)
        {
            return std::any_cast<SparseArray<Component> &>(_componentsArrays[std::type_index(typeid(Component))])
                .insertAt(to._id, c);
        }

        /**
         * This function is used to emplace a component with given parameters of this component
         * @tparam Component The type of component you want to emplace
         * @tparam Params The parameters' type of the component you want to emplace
         * @param to The Entity in which you want to emplace component
         * @param p Parameters of the component you want to emplace
         * @return the SparseArray<Component> reference of the component
         */
        template <typename Component, typename... Params>
        typename SparseArray<Component>::referenceType emplaceComponent(Entity const &to, Params &&...p)
        {
            return std::any_cast<SparseArray<Component> &>(_componentsArrays[std::type_index(typeid(Component))])
                .emplaceAt(to._id, p...);
        }
        /**
         * This function is used to remove a component into an Entity given as parameter
         * @tparam Component The type of the component you want to remove
         * @param from The Entity in which you want to remove component
         */
        template <typename Component> void removeComponent(Entity const &from)
        {
            std::any_cast<SparseArray<Component> &>(_componentsArrays.at(std::type_index(typeid(Component))))[from] =
                std::nullopt;
        }

      private:
        /**
         * Private member _components_array represents the group of component already registered in the Registry class
         */
        std::unordered_map<std::type_index, std::any> _componentsArrays;

        /**
         * Private member _eraseFunctions represents self erase function of each component
         */
        std::vector<std::function<void(Registry &, Entity const &)>> _eraseFunctions;

        /**
         * Private member _entitiesBin represents the bin of every deleted component, used to recover entity instead of
         * creating another one
         */
        std::vector<std::size_t> _entitiesBin;

        /**
         * The total number of entity present in the Registry class
         */
        std::size_t _lastEntity;
    };
} // namespace ecs
