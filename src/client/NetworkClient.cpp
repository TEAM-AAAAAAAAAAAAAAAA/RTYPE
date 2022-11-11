/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Client
*/

#include "NetworkClient.hpp"
#include <iostream>

namespace network
{
    Client &Client::getInstance()
    {
        static Client _Instance;
        return _Instance;
    }

} // namespace network