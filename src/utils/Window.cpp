#ifdef CLIENT_COMPILATION_MODE
#include "Window.hpp"

namespace utils
{
    sf::RenderWindow Window::_Instance(sf::RenderWindow(sf::VideoMode(utils::constant::mapWidth, utils::constant::mapHeight), "r-type"));
} // namespace utils
#endif
