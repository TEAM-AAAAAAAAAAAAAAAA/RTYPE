/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** Room
*/

#pragma once

#include <iostream>
#include <vector>
#include "Engine.hpp"
#include "LockedQueue.hpp"

class Room {
  public:
    Room(char id, std::string name) : _id(id), _name(name), _nbPlayers(0) {};

    ~Room();

    void addPlayer(char playerId)
    {
        _players.push_back(playerId);
        _nbPlayers++;
    }

    void removePlayer(char playerId)
    {
        for (auto it = _playerIds.begin(); it != _playerIds.end(); it++) {
            if (*it == playerId) {
                _players.erase(it);
                _nbPlayers--;
                break;
            }
        }
    }

  private:
    std::string _name;
    char _id;
    char _nbPlayers;
    ecs::Engine _engine;
    LockedQueue<Message> _receivedMessages;
    std::vector<std::char, 4> _playerIds;
};