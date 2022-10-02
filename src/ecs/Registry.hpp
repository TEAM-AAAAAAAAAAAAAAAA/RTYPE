#pragma once

#include <unordered_map>
#include <typeindex>
#include <any>
#include <functional>
#include "SparseArray.hpp"
#include "Entity.hpp"
#include <exception>
#include <iostream>

namespace ecs {

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
            template<class Component>
            SparseArray<Component> &registerComponent() {
                _componentsArrays[std::type_index(typeid(Component))] = SparseArray<Component>();

                std::function<void(Registry &, Entity const &)> erase_func = [](Registry &r, Entity const &e) {
                    SparseArray<Component> &array = r.template getComponents<Component>();
                    array.erase(e);
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
            template<class Component>
            SparseArray<Component> &getComponents() {
                return std::any_cast<SparseArray<Component> &>(
                        _componentsArrays.at(std::type_index(typeid(Component))));
            }

            /**
             * This function is used to get all components already registered in the Registry class
             * following the given component template as const
             * @tparam Component The type of components you want to get
             * @return The const SparseArray of components you asked
             */
            template<class Component>
            SparseArray<Component> const &getComponents() const {
                return std::any_cast<SparseArray<Component>>(_componentsArrays.at(std::type_index(typeid(Component))));
            }

            /**
             * This function is used to create a new entity if it doesn't exists in the _entitiesBin,
             * otherwise it recover it from the bin
             * @return The entity just created (id)
             */
            Entity spawn_entity() {
                if (_entitiesBin.empty()) {
                    _lastEntity++;
                    return Entity(_lastEntity - 1);
                }
                _entitiesBin.erase(_entitiesBin.begin());
                return _entitiesBin.front();
            }

            /**
             * This function is used to get the id of the Entity following the give index
             * @param idx The index of the entity whose id is desired
             * @return The id of the Entity if it exists, std::npos otherwise
             */
//            TODO: Need to implement properly
//            Entity entityFromIndex(std::size_t idx)
//            {
//                std::size_t first = _entitiesBin.begin()->_id;
//                std::size_t last = _entitiesBin.end()->_id;
//
//                if (idx >= _lastEntity || std::find(first, last, idx). != last)
//                    return Entity::npos;
//                return Entity(idx);
//            }

            /**
             * This is used to delete the given Entity (id)
             * For optimisation purposes, Registry class push it in the _entitiesBin
             * @param e The Entity you want to kill
             */
            void killEntity(Entity const &e)
            {
                for (const auto& erase_func: _eraseFunctions)
                    erase_func(*this, e);
                _entitiesBin.push_back(e);
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
            template<typename Component>
            typename SparseArray<Component>::referenceType addComponent(Entity const &to, Component &&c) {
                return std::any_cast<SparseArray<Component> &>(
                        _componentsArrays[std::type_index(typeid(Component))]).insertAt(to, c);
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
                return std::any_cast<SparseArray<Component> &>(
                        _componentsArrays[std::type_index(typeid(Component))]).insertAt(to, Component(p...));
            }
            /**
             * This function is used to remove a component into an Entity given as parameter
             * @tparam Component The type of the component you want to remove
             * @param from The Entity in which you want to remove component
             */
            template <typename Component>
            void removeComponent(Entity const &from)
            {
                std::any_cast<SparseArray<Component>&>(_componentsArrays.at(std::type_index(typeid(Component))))[from] = std::nullopt;
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
             * Private member _entitiesBin represents the bin of every deleted component, used to recover entity instead of creating another one
             */
            std::vector<Entity> _entitiesBin;

            /**
             * The total number of entity present in the Registry class
             */
            std::size_t _lastEntity;
    };
}
