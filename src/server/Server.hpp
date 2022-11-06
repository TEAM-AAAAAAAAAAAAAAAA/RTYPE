#pragma once
#include <array>
#include <atomic>
#include <boost/asio.hpp>
#include <boost/asio/post.hpp>
#include <boost/bind/bind.hpp>
#include <ctime>
#include <iostream>
#include <map>
#include <string>
#include <thread>
#include "LockedQueue.hpp"
#include <boost/asio/thread_pool.hpp>
#include <boost/shared_ptr.hpp>

using boost::asio::ip::udp;

typedef std::map<uint32_t, udp::endpoint> ClientList;
typedef ClientList::value_type Client;

/**
 * Server class which is used by the game server to communicate with the client
 */
namespace network
{
    class Server {
      public:
        /**
         * Default destructor of the server Class, stopping the ioService & make all the threads join
         */
        ~Server()
        {
            _ioService.stop();
            _socket.close();
            _serviceThread.join();
            _outgoingService.join();
        }

        /**
         * This function allows us to check if the server has received messages
         *@return true if there are messages
         */
        static bool hasMessages() { return !_Instance._receivedMessages.empty(); };

        /**
         * Used to send a message to a client given as parameter
         * @param message The message you want to send
         * @param clientID The id of the client you want to communicate with
         */
        static void sendToClient(const Message &message, uint32_t clientID)
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
        static void sendToAll(const Message &message)
        {
            for (auto client : _Instance._clients)
                _Instance.send(message, client.second);
        }

        /**
         * Get the amount of clients that are connected
         * @return Amount of connected clients
         */
        static size_t getClientCount() { return _Instance._clients.size(); }

        /**
         * Get the ID of client from the clients array
         * @param index the index for the array
         * @return client ID of client n
         */
        static uint32_t getClientIdByIndex(size_t index)
        {
            auto it = _Instance._clients.begin();
            for (int i = 0; i < index; i++)
                ++it;
            return it->first;
        }

        /**
         * Getters & Setters of the Server Class
         */

        static LockedQueue<ServerMessage> &getOutgoingMessages() { return _Instance._outgoingMessages; }

        static LockedQueue<ClientMessage> &GetReceivedMessages() { return _Instance._receivedMessages; }

      private:
        /**
         * Locked queue of all unprocessed incoming messages
         */
        LockedQueue<ServerMessage> _outgoingMessages;

        /**
         * Locked queue of all unprocessed received messages
         */
        LockedQueue<ClientMessage> _receivedMessages;

        /**
         * All network related variables
         */
        boost::asio::io_service _ioService;
        udp::endpoint _serverEndpoint;
        udp::endpoint _remoteEndpoint;
        Message _recvBuffer;
        udp::socket _socket;

        /**
         * Threads used by the server class
         */
        std::thread _serviceThread;
        std::thread _outgoingService;

        /**
         * Starts the reception of messages for the server
         */
        void startReceive()
        {
            _recvBuffer.fill(0);
            _socket.async_receive_from(boost::asio::buffer(_recvBuffer), _remoteEndpoint,
                [this](std::error_code ec, std::size_t bytesRecvd) { this->handleReceive(ec, bytesRecvd); });
        }

        /**
         * Used to push incoming messages in _receivedMessages array if no error occurs, display the message of the
         * error otherwise
         * @param error
         * @param bytesTransferred
         */
        void handleReceive(const std::error_code &error, std::size_t bytesTransferred)
        {
            if (!error) {
                try {
                    auto message = ClientMessage(std::array(_recvBuffer), getOrCreateClientID(_remoteEndpoint));
                    if (!message.first.empty()) {
                        _receivedMessages.push(message);
                        for (const auto &c : message.first) {
                            std::cerr << c;
                        }
                        std::cerr << std::endl;
                    }
                } catch (std::exception ex) {
                    std::cerr << "handleReceive: Error parsing incoming message:" << ex.what() << std::endl;
                } catch (...) {
                    std::cerr << "handleReceive: Unknown error while parsing incoming message" << std::endl;
                    ;
                }
            } else {
                std::cerr << "handleReceive: error: " << error.message() << " while receiving from address "
                          << _remoteEndpoint << std::endl;
            }
            startReceive();
        }

        /**
         * Main function of the communication between server and clients, catch and throw errors if any
         */
        void receiveIncoming()
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
        int32_t getOrCreateClientID(udp::endpoint endpoint)
        {
            for (const auto &client : _clients)
                if (client.second == endpoint)
                    return client.first;

            auto id = ++_nextClientID;
            _clients.insert(Client(id, endpoint));
            return id;
        }

        /**
         * Send a specified message to a specified client
         * @param message  The message to send
         * @param endpoint The client you want to communicate with
         */
        void send(const Message &message, udp::endpoint endpoint)
        {
            _socket.async_send_to(
                boost::asio::buffer(message), endpoint, [](std::error_code ec, std::size_t bytesRecvd) {});
        }
        /**
         * Used to send message to clients with the outgoingMessages array isn't empty
         */
        [[noreturn]] void sendOutgoing()
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
         *  Clients of the server
         */
        ClientList _clients;
        int _nextClientID;

        /**
         * Default Constructor of the Server Class, initializing every part of it, socket, endpointk,
         * serviceThread, _nextClientID, _outgoingService
         * @param localPort The open localPort of the server
         */
        Server(unsigned short localPort = 8000)
            : _socket(_ioService, udp::endpoint(udp::v4(), localPort)), _serviceThread(&network::Server::receiveIncoming, this),
              _nextClientID(0L), _outgoingService(&network::Server::sendOutgoing, this)
        {
            std::cerr << "Starting server on port " << localPort << std::endl;
        };

        static Server _Instance;
    };
} // namespace network