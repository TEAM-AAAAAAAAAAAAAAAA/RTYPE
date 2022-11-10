/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** Server
*/

#include "Server.hpp"

namespace network
{
    Server &Server::getInstance()
    {
        static Server _Instance;
        return _Instance;
    }
} // namespace network