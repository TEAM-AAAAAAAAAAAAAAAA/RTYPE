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
    /**
     * SFML window wrapper for the R-Type Project
     */
    class Window : public sf::RenderWindow {
      public:
        /**
         * Default constructor of window class, setting by default the FrameLimit to 60 (representing 65 fps)
         */
        Window() : sf::RenderWindow(sf::VideoMode(ecs::constant::mapWidth, ecs::constant::mapHeight), "r-type")
        {
            this->setFramerateLimit(60);
        }
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
