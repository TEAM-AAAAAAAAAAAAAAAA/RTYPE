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

    /**
     * Default Constructor of the Server Class, initializing every part of it, socket, endpointk,
     * serviceThread, _nextClientID, _outgoingThread
     * @param localPort The open localPort of the server
     */
    Server::Server(unsigned short localPort)
        : _socket(_ioService, udp::endpoint(udp::v4(), localPort)), _serviceThread(&Server::runService, this),
          _nextClientID(0L), _outgoingThread(&Server::sendOutgoing, this)
    {
        std::cerr << "Starting server on port " << localPort << std::endl;
    };

    /**
     * Default destructor of the server Class, stopping the ioService & make all the threads join
     */
    Server::~Server()
    {
        _ioService.stop();
        _socket.close();
        _serviceThread.join();
        _outgoingThread.join();
    }

    /**
     * Used to able the server to receive message from clients
     */
    void Server::startReceive()
    {
        _recvBuffer.fill(0);
        _socket.async_receive_from(boost::asio::buffer(_recvBuffer), _remoteEndpoint,
            [this](std::error_code ec, std::size_t bytesRecvd) { this->handleReceive(ec, bytesRecvd); });
    }

    /**
     * Used to check if an error occurs in a specify client, erasing it if it happens
     * @param errorCode used to know what kind of errors occurred
     * @param endpoint The endpoint where the error occurred
     */
    void Server::handleRemoteError(const std::error_code errorCode, const udp::endpoint& endpoint)
    {
        bool found = false;
        int32_t id;
        for (const auto &client : _clients)
            if (client.second == endpoint) {
                found = true;
                id = client.first;
                break;
            }
        if (!found)
            return;
        _clients.erase(id);
    }

    /**
     * Used to push incoming messages in _incomingMessages array if no error occurs, display the message of the error otherwise
     * @param error
     * @param bytesTransferred
     */
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

    /**
     * Used to send message to clients with the outgoingMessages array isn't empty
     */
    [[noreturn]] void Server::sendOutgoing()
    {
        while (1) {
            if (!_outgoingMessages.empty()) {
                ServerMessage message = _outgoingMessages.pop();
                if (message.second.empty())
                    sendToAll(message.first);
                else
                    for (auto &client : message.second)
                        sendToClient(message.first, client);
            }
        }
    }

    /**
     * Send a specified message to a specified client
     * @param message  The message to send
     * @param endpoint The client you want to communicate with
     */
    void Server::send(const Message &message, udp::endpoint endpoint)
    {
        _socket.async_send_to(boost::asio::buffer(message), endpoint,
        [this](std::error_code ec, std::size_t bytesSent){});
    }

    /**
     * Main function of the communication between server and clients, catch and throw errors if any
     */
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
    }

    /**
     * Used to get the id of the client given as parameter if it exists, creating it otherwise
     * @param endpoint The given client id
     * @return The id of the client
     */
    int32_t Server::getOrCreateClientID(udp::endpoint endpoint)
    {
        for (const auto &client : _clients)
            if (client.second == endpoint)
                return client.first;

        auto id = ++_nextClientID;
        _clients.insert(Client(id, endpoint));
        return id;
    }

    /**
     * Used to send a message to a client given as parameter
     * @param message The message you want to send
     * @param clientID The id of the client you want to communicate with
     */
    void Server::sendToClient(const Message &message, uint32_t clientID)
    {
        try {
            _Instance.send(message, _Instance._clients.at(clientID));
        } catch (std::out_of_range) {
            std::cerr << "sendToClient : Unknown client ID " << clientID << std::endl;
        }
    }

    /**
     * Used to send a message to every available clients
     * @param message The message you want to send
     */
    void Server::sendToAll(const Message &message)
    {
        for (auto client : _Instance._clients)
            _Instance.send(message, client.second);
    }

    /**
     * Getters & Setters of the Server Class
     */
    LockedQueue<ServerMessage> &Server::getOutgoingMessages() { return _Instance._outgoingMessages; }

    LockedQueue<ClientMessage> &Server::getIncomingMessages() { return _Instance._incomingMessages; }

    size_t Server::getClientCount() { return _Instance._clients.size(); }

    uint32_t Server::getClientIdByIndex(size_t index)
    {
        auto it = _Instance._clients.begin();
        for (int i = 0; i < index; i++)
            ++it;
        return it->first;
    }

    bool Server::hasMessages() { return !_Instance._incomingMessages.empty(); };
} // namespace network