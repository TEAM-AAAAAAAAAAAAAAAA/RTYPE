/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** Window
*/

#pragma once

#ifdef CLIENT_COMPILATION_MODE
    #include "SFML/Graphics.hpp"
    #include "Constant.hpp"

namespace ecs::utils
{
    class Window : public sf::RenderWindow {
      public:
        Window() : sf::RenderWindow(sf::VideoMode(ecs::constant::mapWidth, ecs::constant::mapHeight), "r-type") {}
    };
} // namespace ecs::utils
#else
namespace ecs::utils
{
    class Window {
      public:
        inline bool isOpen() { return true; }
    };
} // namespace ecs::utils
#endif
