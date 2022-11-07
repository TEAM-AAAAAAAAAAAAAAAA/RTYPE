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
        explicit Activable(utils::constant::ButtonType type, bool hidle = false) : _type(type), _hidle(hidle), _selected(false){};
        /**
         * @brief Get the state of the object
         *
         * @return true
         * @return false
         */
        inline bool getHidle() const { return _hidle; };
        /**
         * @brief Set the state of object
         *
         * @param active boolean
         */
        inline void setHidle(bool hidle) { _hidle = hidle; };
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
        inline utils::constant::ButtonType getType() const { return _type; };

      private:
        /**
         * @brief state hidle of the object
         *
         */
        bool _hidle;
        /**
         * @brief state selected of the object
         *
         */
        bool _selected;
        /**
         * @brief type of the activable object
         *
         */
        utils::constant::ButtonType _type;
    };
} // namespace ecs::component
