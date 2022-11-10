/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** HubServer
*/

#pragma once

#include <array>
#include <iostream>
#include <map>
#include <string>
#include "../server/Server.hpp"
#include "../utils/Constant.hpp"

using chrono = std::chrono::high_resolution_clock;
using chronoDuration = std::chrono::duration<double, std::milli>;

class HubServer {
  public:
    HubServer(int port)
    {
        network::ServerMessage response;
        char **buffer = new char *[2];
        _pids.fill(0);
        _port = port;
        for (size_t i = 0; i < 4; i++) {
            _pids[i] = fork();
            if (_pids[i] == -1) {
                std::cerr << "Error while forking" << std::endl;
                exit(84);
            }
            if (_pids[i] == 0) {
                buffer[0] = (char *)(std::to_string(_port + i).c_str());
                buffer[1] = (char *)(std::to_string(_port + i).c_str());
                execve("./r-type_server", buffer, nullptr);
                exit(0);
            } else {
                _serverPorts[i] = _port + i;
                _serverSlots[i] = 0;
                _serverIds[i] = network::Server::connect("localhost", std::to_string(_port + i));
                response.first[0] = 68;
                response.second.push_back(_serverIds[i]);
                network::Server::getOutgoingMessages().push(response);
            }
        }
    };

    ~HubServer(){};

    void handleIncomingMessages()
    {
        while (network::Server::hasMessages()) {
            char **buffer = new char *[2];
            buffer[0] = (char *)(std::to_string(_port).c_str());
            buffer[1] = (char *)(std::to_string(_port).c_str());
            network::ClientMessage msg = network::Server::GetReceivedMessages().pop();
            network::ServerMessage response;
            response.second.clear();
            response.first.fill(0);
            _serverSlots.fill(0);
            _serverIds.fill(0);
            if (msg.first[0] == 0) {
                response.first[0] = 64;
                response.second.push_back(msg.second);
                network::Server::getOutgoingMessages().push(response);
            }
            if (msg.first[0] == 128) {
                response.second.push_back(msg.second);
                int clientPort = (unsigned char)msg.first[1] << 8U | (unsigned char)msg.first[2];
                for (size_t i = 0; i < _pids.size(); i++) {
                    if (_pids[i] != 0 && _serverPorts[i] != 0) {
                        int tmp = 0;
                        tmp = _serverPorts[i] >> 8;
                        response.first[0] = 129;
                        response.first[1] = _serverNames[i][0];
                        response.first[2] = _serverNames[i][1];
                        response.first[3] = _serverNames[i][2];
                        response.first[4] = _serverNames[i][3];
                        response.first[5] = tmp;
                        response.first[6] = _serverPorts[i] & 0xff;
                        response.first[7] = _serverSlots[i];
                        network::Server::getOutgoingMessages().push(response);
                    }
                }
            }
            if (msg.first[0] == 255) {
                int clientPort = (unsigned char)msg.first[1] << 8U | (unsigned char)msg.first[2];
                size_t i = 0;
                for (; i < _pids.size(); i++) {
                    if (_serverPorts[i] == clientPort) {
                        break;
                    }
                }
                response.second.push_back(msg.second);
                if (_serverPorts[i] == clientPort && _serverSlots[i] < 4) {
                    _serverSlots[i]++;
                    response.first[0] = 65;
                    network::Server::getOutgoingMessages().push(response);
                } else {
                    response.first[0] = 66;
                    network::Server::getOutgoingMessages().push(response);
                }
            }
        }
    };

    void sendOutgoingMessages()
    {
        static auto clock = chrono::now();
        if (utils::constant::chronoDuration(utils::constant::chrono::now() - clock).count() > 200) {
            clock = utils::constant::chrono::now();
            for (size_t i = 0; i < _pids.size(); i++) {
                if (_pids[i] != 0 && _serverIds[i] != 0) {
                    network::ServerMessage response;
                    response.second.clear();
                    response.first.fill(0);
                    response.second.push_back(_serverIds[i]);
                    response.first[0] = 127;
                }
            }
        }
    }

  private:
    int _port;
    std::array<pid_t, 4> _pids;
    std::array<std::array<char, 4>, 4> _serverNames;
    std::array<char, 4> _serverSlots;
    std::array<int, 4> _serverPorts;
    std::array<uint32_t, 4> _serverIds;
};