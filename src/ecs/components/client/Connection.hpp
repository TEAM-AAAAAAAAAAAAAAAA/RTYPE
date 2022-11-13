/*
** EPITECH PROJECT, by hourcadettej on 11/12/22.
** rtype
** File description:
** rtype
*/

#pragma once
#include "../../../../src/client/NetworkClient.hpp"

namespace ecs::component {
    struct Connection {

            Connection() : _port(asset::AssetLoader::GetServerInfo("port")), _host(asset::AssetLoader::GetServerInfo("host")), _isSet(false) {}

            void setPort(int port) {
                _port = std::to_string(port);
                _isSet = true;
            }
            inline std::string getPort() const {return _port;}
            inline void setHost(const std::string &host) {_host = host;}
            inline std::string getHost() const {return _host;}
            inline bool getIsSet() const {return _isSet;}
            inline void setIsSet(bool isSet) {_isSet = isSet;}
            void setClientConnection() {
                network::Message msg;
                msg.fill(0);
                network::Client::setHost(_host);
                network::Client::setPort(_port);
                network::Client::connect();
                network::Client::getOutgoingMessages().push(msg);
            }
        private:
            std::string _port;
            std::string _host;
            bool _isSet;
    };
}
