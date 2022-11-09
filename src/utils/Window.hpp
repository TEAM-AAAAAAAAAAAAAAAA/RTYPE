/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** Window
*/

#pragma once

#ifdef CLIENT_COMPILATION_MODE
    #include "Constant.hpp"
    #include "SFML/Graphics.hpp"

namespace utils
{
    /**
     * SFML window wrapper for the R-Type client
     */
    class Window {
      public:
        /**
         * Default constructor of window class, setting by default the FrameLimit to 60 (representing 65 fps)
         */
        Window() {}
        ~Window() {}
        // static inline sf::RenderWindow &get() { return _Instance; }
        static inline bool isOpen() { return getInstance().isOpen(); }

        static sf::RenderWindow &getInstance()
        {
            static sf::RenderWindow instance(
                sf::RenderWindow(sf::VideoMode(utils::constant::mapWidth, utils::constant::mapHeight), "r-type"));
            return instance;
        }
    };
} // namespace utils
#else
namespace utils
{
    /**
     * Placeholder window wrapper for the R-Type server
     */
    class Window {
      public:
        ~Window() {}
        static inline bool isOpen() { return true; }
    };
} // namespace utils
#endif