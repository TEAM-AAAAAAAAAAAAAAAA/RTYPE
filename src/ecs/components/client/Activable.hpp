/*
** EPITECH PROJECT, by hourcadettej on 10/29/22.
** rtype
** File description:
** rtype
*/

#pragma once

#include <string>
#include <utility>
#include "Constant.hpp"

namespace ecs::component
{
    struct Activable {
        /**
         * @brief Construct a new Activable object (true or false state)
         *
         * @param active default at false
         */
        explicit Activable(utils::constant::ButtonActionType type, bool hover = false) : _type(type), _hover(hover), _selected(false){};
        /**
         * @brief Get the state of the object
         *
         * @return true
         * @return false
         */
        inline bool getHover() const { return _hover; };
        /**
         * @brief Set the state of object
         *
         * @param active boolean
         */
        inline void setHover(bool hover) { _hover = hover; };
        /**
         * @brief Get the state of the object
         *
         */
        inline bool getSelected() const { return _selected; };
        /**
         * @brief Set the state of object
         *
         * @param selected boolean
         */
        inline void setSelected(bool selected) { _selected = selected; };

        /*
         * @brief Get the type of the object
         *
         */
        inline utils::constant::ButtonActionType getType() const { return _type; };

      private:
        /**
         * @brief state hover of the object
         *
         */
        bool _hover;
        /**
         * @brief state selected of the object
         *
         */
        bool _selected;
        /**
         * @brief type of the activable object
         *
         */
        utils::constant::ButtonActionType _type;
    };
} // namespace ecs::component
