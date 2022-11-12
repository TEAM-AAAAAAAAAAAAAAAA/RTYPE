/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** entrypoint
*/

#include <iostream>
#include <string>
#include "HubServer.hpp"
#include "../server/Server.hpp"

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << argc << std::endl;
        std::cerr << "Usage: ./r-type_server [port]" << std::endl;
        return 1;
    }
    try {
        if (std::stoi(argv[1]) < 0) {
            std::cerr << "Port must be greater than 0" << std::endl;
            return 84;
        }
    } catch (std::exception &e) {
        std::cerr << "Port must be a number" << std::endl;
        return 84;
    }
    int base = std::stoi(argv[1]);
    network::Server::start(std::stoi(argv[1]));
    HubServer hubServer(base);
    while (1)
        hubServer.handleIncomingMessages();
    return 0;
}
