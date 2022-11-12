/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** InputMap
*/

#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <string>

namespace utils {

    /** @addtogroup Input
    * @{
    */

    /**
     * Returns the string associated with the @a key
     * @details The returned string is identical to the enum identifier. For example:
     * @code
     * utils::toString(sf::Keyboard::A) == "A"
     * @endcode
     * @throw std::out_of_range if @a key is not a valid key
     */
    std::string toString(sf::Keyboard::Key key);

    /**
     * Return the key interpretation of @a string
     * @details The passed string must be identical to the enum identifier. For example:
     * @code
     * utils::toKey("A") == sf::Keyboard::A
     * @endcode
     * @param string
     * @throw std::out_of_range if @a string is not a valid key
     */
    sf::Keyboard::Key toKey(std::string string);

    /** @} */
};


