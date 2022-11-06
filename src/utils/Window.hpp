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
        Window() { _Instance.setFramerateLimit(60); }
        ~Window() {}
        static inline sf::RenderWindow &get() { return _Instance; }
        static inline bool isOpen() { return _Instance.isOpen(); }

      private:
        static sf::RenderWindow _Instance;
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
        inline bool isOpen() { return open; }
        bool open = true;
    };
} // namespace utils
#endif
