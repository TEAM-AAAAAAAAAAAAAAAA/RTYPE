/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** ClientSocket
*/

#pragma once

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include "NetowrkClient.hpp"

using boost::asio::ip::udp;

namespace ecs::component
{
    /**
     * ClientSocket is the component that the client will use to send and receive messages
     */
    struct ClientSocket {
    };
} // namespace ecs::component
