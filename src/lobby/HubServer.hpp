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

class HubServer {
  public:
    HubServer(int port)
    {
        _pids.fill(0);
        _port = port;
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
            if (msg.first[0] == 0) {
                std::array<char, 4> name;
                std::copy(msg.first.begin() + 1, msg.first.begin() + 5, name.begin());
                _clientNames.push_back(std::pair(msg.second, name));
                response.second.push_back(msg.second);
                network::Server::getOutgoingMessages().push(response);
            }
            if (msg.first[0] == 128) {
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
                    }
                }
            }
            if (msg.first[0] == 254) {
                char **buffer = new char *[2];
                size_t i = 0;
                for (; i < _pids.size(); i++) {
                    if (_pids[i] == 0) {
                        break;
                    }
                }
                if (_pids[i] != 0)
                    continue;
                buffer[0] = (char *)(std::to_string(_port + i).c_str());
                buffer[1] = (char *)(std::to_string(_port + i).c_str());
                _pids[i] = fork();
                if (_pids[i] == -1) {
                    std::cerr << "Fork failed" << std::endl;
                    continue;
                }
                if (_pids[i] == 0) {
                    execve("./r-type_server", buffer, nullptr);
                    exit(0);
                } else {
                    _serverPorts[i] = _port + i;
                    _serverSlots[i] = 0;
                    for (auto &client : _clientNames) {
                        if (client.first == msg.second) {
                            _serverNames[i] = client.second;
                            break;
                        }
                    }
                }
            }
            if (msg.first[0] == 255) {
                int clientPort = (unsigned char)msg.first[1] << 8U | (unsigned char)msg.first[2];
                for (size_t i = 0; i < _pids.size(); i++) {
                    if (_serverPorts[i] == clientPort) {
                        _serverSlots[i] += 1;
                        break;
                    }
                }
                for (auto &client : _clientNames) {
                    if (client.first == msg.second) {
                        _clientNames.erase(
                            std::remove(_clientNames.begin(), _clientNames.end(), client), _clientNames.end());
                        
                        break;
                    }
                }
            }
        }
    };

  private:
    int _port;
    std::array<pid_t, 10> _pids;
    std::array<std::array<char, 4>, 10> _serverNames;
    std::array<char, 10> _serverSlots;
    std::array<int, 10> _serverPorts;
    std::vector<std::pair<unsigned int, std::array<char, 4>>> _clientNames;
};