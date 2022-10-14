/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** Server
*/

#include "Server.hpp"

namespace network
{
    Server Server::_Instance;

    Server::Server(unsigned short localPort)
        : _socket(_ioService, udp::endpoint(udp::v4(), localPort)), _serviceThread(&Server::runService, this),
          _nextClientID(0L), _interpretThread(&Server::interpretIncoming, this),
          _outgoingThread(&Server::sendOutgoing, this)
    {
        std::cerr << "Starting server on port " << localPort << std::endl;
    };

    Server::~Server()
    {
        _ioService.stop();
        _serviceThread.join();
    }

    void Server::startReceive()
    {
        _recvBuffer.fill(0);
        _socket.async_receive_from(boost::asio::buffer(_recvBuffer), _remoteEndpoint,
            [this](std::error_code ec, std::size_t bytesRecvd) { this->handleReceive(ec, bytesRecvd); });
    }

    void Server::handleRemoteError(const std::error_code errorCode, const udp::endpoint endpoint)
    {
        bool found = false;
        int32_t id;
        for (const auto &client : _clients)
            if (client.second == endpoint) {
                found = true;
                id = client.first;
                break;
            }
        if (found == false)
            return;
        _clients.erase(id);
    }

    void Server::handleReceive(const std::error_code &error, std::size_t bytesTransferred)
    {
        if (!error) {
            try {
                auto message = ClientMessage(std::array(_recvBuffer), getOrCreateClientID(_remoteEndpoint));
                if (!message.first.empty())
                    _incomingMessages.push(message);
            } catch (std::exception ex) {
                std::cerr << "handleReceive: Error parsing incoming message:" << ex.what() << std::endl;
            } catch (...) {
                std::cerr << "handleReceive: Unknown error while parsing incoming message" << std::endl;
                ;
            }
        } else {
            std::cerr << "handleReceive: error: " << error.message() << " while receiving from address "
                      << _remoteEndpoint << std::endl;
            handleRemoteError(error, _remoteEndpoint);
        }
        startReceive();
    }

    void Server::sendOutgoing(void)
    {
        while (1) {
            if (!_outgoingMessages.empty())
                sendToAll(_outgoingMessages.pop().first);
        }
    }

    void Server::send(const std::array<char, 10> &message, udp::endpoint endpoint)
    {
        _socket.send_to(boost::asio::buffer(message), endpoint);
    }

    void Server::runService()
    {
        startReceive();
        while (!_ioService.stopped()) {
            try {
                _ioService.run();
            } catch (const std::exception &e) {
                std::cerr << "Server: Network exception: " << e.what() << std::endl;
            } catch (...) {
                std::cerr << "Server: Network exception: unknown" << std::endl;
            }
        }
        std::cerr << "Server network thread stopped" << std::endl;
    };

    int32_t Server::getOrCreateClientID(udp::endpoint endpoint)
    {
        for (const auto &client : _clients)
            if (client.second == endpoint)
                return client.first;

        auto id = ++_nextClientID;
        _clients.insert(Client(id, endpoint));
        return id;
    };

    void Server::sendToClient(const std::array<char, 10> &message, uint32_t clientID)
    {
        try {
            _Instance.send(message, _Instance._clients.at(clientID));
        } catch (std::out_of_range) {
            std::cerr << "sendToClient : Unknown client ID " << clientID << std::endl;
        }
    };

    void Server::sendToAll(const std::array<char, 10> &message)
    {
        for (auto client : _Instance._clients)
            _Instance.send(message, client.second);
    }

    void Server::interpretIncoming(void)
    {
        network::ClientMessage message;
        while (1) {
            if (!_incomingMessages.empty())
                message = _incomingMessages.pop();
            // Deserialize and add as task
        }
    }

    size_t Server::getClientCount() { return _Instance._clients.size(); }

    uint32_t Server::getClientIdByIndex(size_t index)
    {
        auto it = _Instance._clients.begin();
        for (int i = 0; i < index; i++)
            ++it;
        return it->first;
    };

    bool Server::hasMessages() { return !_Instance._incomingMessages.empty(); };

    LockedQueue<ServerMessage> &Server::getOutgoingMessages() { return _Instance._outgoingMessages; }
} // namespace network