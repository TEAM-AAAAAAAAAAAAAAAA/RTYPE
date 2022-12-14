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
#include "../utils/Constant.hpp"
#include "LockedQueue.hpp"
#include <boost/asio/thread_pool.hpp>
#include <boost/shared_ptr.hpp>

using chrono = std::chrono::high_resolution_clock;
using chronoDuration = std::chrono::duration<double, std::milli>;
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
            _isStopping = true;
            _serviceThread.join();
            _outgoingService.join();
            _socket.close();
        }

        /**
         * This function allows us to check if the server has received messages
         *@return true if there are messages
         */
        static bool hasMessages() { return !getInstance()._receivedMessages.empty(); };

        /**
         * Used to send a message to a client given as parameter
         * @param message The message you want to send
         * @param clientID The id of the client you want to communicate with
         */
        static void sendToClient(const Message &message, uint32_t clientID)
        {
            try {
                getInstance().send(message, getInstance()._clients.at(clientID));
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
            for (auto client : getInstance()._clients)
                if (client.first != getInstance()._hubID)
                    getInstance().send(message, client.second);
        }

        /**
         * Get the amount of clients that are connected
         * @return Amount of connected clients
         */
        static size_t getClientCount() { return getInstance()._clients.size() - (getInstance()._hubID != -1); }

        /**
         * Get the ID of client from the clients array
         * @param index the index for the array
         * @return client ID of client n
         */
        static uint32_t getClientIdByIndex(size_t index)
        {
            auto it = getInstance()._clients.begin();
            for (int i = 0; i < index; i++)
                ++it;
            return it->first;
        }

        static uint32_t connect(std::string host, std::string port)
        {
            udp::resolver resolver(getInstance()._ioService);
            udp::resolver::query query(udp::v4(), host, port);
            udp::endpoint endpoint = *resolver.resolve(query);
            return getInstance().getOrCreateClientID(endpoint);
        }

        /**
         * Remove a client from the clients map
         * @param clientId the clients ID
         */
        static void removeClient(uint32_t clientID)
        {
            if (getInstance()._clients.find(clientID) != getInstance()._clients.end())
                getInstance()._clients.erase(clientID);
            if (getInstance()._clientToEntID.find(clientID) != getInstance()._clientToEntID.end())
                getInstance()._clientToEntID.erase(clientID);
            if (getInstance()._clientLastPing.find(clientID) != getInstance()._clientLastPing.end())
                getInstance()._clientLastPing.erase(clientID);
        }

        static inline void start(unsigned short localPort)
        {
            if (getInstance()._isRunning)
                return;
            getInstance()._socket = udp::socket(getInstance()._ioService, udp::endpoint(udp::v4(), localPort));
            getInstance()._isRunning = true;
            std::cerr << "Server started on port " << localPort << std::endl;
        }

        /**
         * Getters & Setters of the Server Class
         */

        static LockedQueue<ServerMessage> &getOutgoingMessages() { return getInstance()._outgoingMessages; }

        static LockedQueue<ClientMessage> &getReceivedMessages() { return getInstance()._receivedMessages; }

        static std::map<unsigned int, size_t> &getClientToEntID() { return getInstance()._clientToEntID; }

        static std::map<unsigned int, std::chrono::time_point<std::chrono::high_resolution_clock>> &getClientLastPings() { return getInstance()._clientLastPing; }

        static std::chrono::high_resolution_clock::time_point getLastPing(uint32_t clientID)
        {
            for (const auto &client : getInstance()._clientLastPing)
                if (client.first == clientID)
                    return client.second;
            return chrono::now();
        }

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
                    if (_recvBuffer[0] == 68) {
                        _hubID = getOrCreateClientID(_remoteEndpoint);
                        std::cerr << "Hub connected" << std::endl;
                    }
                    auto message = ClientMessage(std::array(_recvBuffer), getOrCreateClientID(_remoteEndpoint));
                    _clientLastPing[getOrCreateClientID(_remoteEndpoint)] = utils::constant::chrono::now();
                    if (!message.first.empty()) {
                        _receivedMessages.push(message);
                        for (const auto &c : message.first) {}
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
            while (!_isRunning) {
                if (_isStopping)
                    return;
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
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
        void sendOutgoing()
        {
            while (!_isRunning) {
                if (_isStopping)
                    return;
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            while (!_ioService.stopped()) {
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
        std::map<unsigned int, size_t> _clientToEntID;
        int _nextClientID;
        int _hubID = -1;

        /**
         * The timestamps of the last received messages from each client
         */
        std::map<uint32_t, std::chrono::high_resolution_clock::time_point> _clientLastPing;

        /**
         * Used to know if the server is running or not
         */
        bool _isRunning = false;
        bool _isStopping = false;

        /**
         * Default Constructor of the Server Class, initializing every part of it, socket, endpointk,
         * serviceThread, _nextClientID, _outgoingService
         * @param localPort The open localPort of the server
         */
        Server()
            : _socket(_ioService), _serviceThread(&network::Server::receiveIncoming, this), _nextClientID(0L),
              _outgoingService(&network::Server::sendOutgoing, this){};

        //        static Server getInstance();
        static Server &getInstance();
    };
} // namespace network