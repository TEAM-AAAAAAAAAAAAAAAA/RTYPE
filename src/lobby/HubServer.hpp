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
#ifdef WIN32
    #include <windows.h>
#endif
#include <stdio.h>
#include "../server/Server.hpp"
#include "../utils/Constant.hpp"

using chrono = std::chrono::high_resolution_clock;
using chronoDuration = std::chrono::duration<double, std::milli>;

class HubServer {
  public:
    HubServer(int port)
    {
        network::ServerMessage response;
        _pids.fill(0);
        _port = port;
#ifdef WIN32
        for (size_t i = 0; i < _processes.size(); i++) {
            STARTUPINFO si;

            ZeroMemory(&si, sizeof(si));
            si.cb = sizeof(si);
            ZeroMemory(&_processes[i], sizeof(_processes[i]));

            if (!CreateProcess(NULL, ("r-type_server " + std::to_string(_port + i + 1)).c_str(), NULL, NULL, FALSE, 0,
                    NULL, NULL, &si, &_processes[i])) {
                std::cerr << "Failed to create process" << std::endl;
                exit(84);
            }
            _serverPorts[i] = _port + i + 1;
            _serverSlots[i] = 0;
            _serverIds[i] = network::Server::connect("localhost", std::to_string(_port + i + 1));
            response.first[0] = 68;
            response.second.push_back(_serverIds[i]);
            network::Server::getOutgoingMessages().push(response);
        }
#else
        for (size_t i = 0; i < _pids.size(); i++) {
            _pids[i] = fork();
            if (_pids[i] == -1) {
                std::cerr << "Error while forking" << std::endl;
                exit(84);
            }
            if (_pids[i] == 0) {
                execl("./r-type_server", "./r-type_server", std::to_string(_port + i + 1).c_str(), nullptr);
                exit(0);
            } else {
                _serverPorts[i] = _port + i + 1;
                _serverSlots[i] = 0;
                _serverIds[i] = network::Server::connect("localhost", std::to_string(_port + i + 1));
                response.first[0] = 68;
                response.second.push_back(_serverIds[i]);
                network::Server::getOutgoingMessages().push(response);
            }
        }
#endif
    };

    ~HubServer()
    {
#ifdef WIN32
        for (size_t i = 0; i < 4; i++) {
            CloseHandle(_processes[i].hProcess);
        }
#else
        for (size_t i = 0; i < _pids.size(); i++) {
            if (_pids[i] != 0)
                kill(_pids[i], SIGKILL);
        }
#endif
    };

    void handleIncomingMessages()
    {
        while (network::Server::hasMessages()) {
            char **buffer = new char *[2];
            buffer[0] = (char *)(std::to_string(_port).c_str());
            buffer[1] = (char *)(std::to_string(_port).c_str());
            network::ClientMessage msg = network::Server::getReceivedMessages().pop();
            network::ServerMessage response;
            response.second.clear();
            response.first.fill(0);
            int msgCode = msg.first[0];
            if (msgCode == 0) {
                std::cout << "NEW CONNEC\n";
                response.first[0] = 64;
                response.second.push_back(msg.second);
                network::Server::getOutgoingMessages().push(response);
            }
            if (msgCode == 60) {
                std::cout << "REFRESH SERVER\n";
                response.second.push_back(msg.second);
                std::cerr << "Sending servers information" << std::endl;
                for (size_t i = 0; i < _serverPorts.size(); i++) {
                    if (_serverPorts[i] != 0 && _serverPorts[i] != 0) {
                        int tmp = 0;
                        tmp = _serverPorts[i] >> 8;
                        response.first[0] = 61;
                        response.first[1] = tmp;
                        response.first[2] = _serverPorts[i] & 0xff;
                        response.first[3] = _serverSlots[i];
                        network::Server::getOutgoingMessages().push(response);
                    }
                }
            }
            if (msgCode == 130) {
                for (size_t i = 0; i < _serverIds.size(); i++) {
                    if (_serverIds[i] == msg.second) {
                        _serverSlots[i] = msg.first[2];
                        break;
                    }
                }
            }
            if (msgCode == 255) {
                int clientPort = (unsigned char)msg.first[1] << 8U | (unsigned char)msg.first[2];
                size_t i = 0;
                for (; i < _serverPorts.size(); i++) {
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
        if (utils::constant::chronoDuration(utils::constant::chrono::now() - clock).count() > 500) {
            clock = utils::constant::chrono::now();
            for (size_t i = 0; i < _serverPorts.size(); i++) {
                if (_serverPorts[i] != 0 && _serverIds[i] != 0) {
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
    /**
     * Main port of the hub server
     */
    int _port;

#ifdef WIN32
    std::array<PROCESS_INFORMATION, 4> _processes;
#else
    std::array<pid_t, 4> _pids;
#endif

    /**
     * Arrays that contain useful information about the servers
     */
    std::array<char, 4> _serverSlots;
    std::array<int, 4> _serverPorts;
    std::array<uint32_t, 4> _serverIds;
};