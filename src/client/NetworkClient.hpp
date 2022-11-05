/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Client
*/

#pragma once

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include "LockedQueue.hpp"

using boost::asio::ip::udp;

namespace network
{
    /**
     * Client class is one of the big parts in the game.
     * It represents the way for the gamer to communicate with the servers by sending and receiving some message.
     * To understand those messages in a more specifically way, just refer to the RFC.
     * Client is able to join a specific server by a given ip & port, communicating with it using sockets & buffers
     */
    class Client {
      public:
        /**
         * Default destructor of the Client Class
         */
        ~Client()
        {
            _Instance._ioService.stop();
            _Instance.stopServices();
            _Instance._socket.close();
        }

        /**
         * Getters & Setters of client Class
         */
        static inline void setHost(const std::string &host) { _Instance._host = host; }

        static void setPort(const std::string &port) { _Instance._port = port; }

        static inline LockedQueue<Message> &getOutgoingMessages() { return _Instance._outgoingMessages; }

        static inline LockedQueue<Message> &getReceivedMessages() { return _Instance._receivedMessages; }

        /**
         * Static methods used to connect to the given server (host, port) using udp::v4
         */
        static void connect()
        {
            _Instance._socket = udp::socket(_Instance._ioService, udp::endpoint(udp::v4(), 0));
            udp::resolver resolver = udp::resolver(_Instance._ioService);
            _Instance._endpoint = *resolver.resolve({udp::v4(), _Instance._host, _Instance._port});
            _Instance.startServices();
        }

        /**
         * Static methods used to disconnect from the given server (host, port) using udp::v4
         */
        static void disconnect()
        {
            _Instance._ioService.stop();
            _Instance._socket.close();
            _Instance.stopServices();
        }

        /**
         * Start the service threads for managing incoming & outgoing messages
         */
        static void startServices()
        {
            _Instance._incomingService = std::thread(&Client::receiveIncoming, &_Instance);
            _Instance._outgoingService = std::thread(&Client::sendOutgoing, &_Instance);
        }

      private:
        /**
         * Private default constructor of the Client Class
         */
        Client() : _socket(_ioService) {};

        /**
         * Service threads for managing incoming & outgoing messages, using the `Client::_outgoingMessages` &
         * `Client::_receivedMessages queues
         */
        std::thread _outgoingService;
        std::thread _incomingService;

        /**
         * Message queues for incoming & outgoing messages
         */
        LockedQueue<Message> _outgoingMessages;
        LockedQueue<Message> _receivedMessages;

        /**
         * Boost Asio service & socket
         */
        boost::asio::io_service _ioService;
        udp::socket _socket;
        udp::endpoint _endpoint;
        std::string _host;
        std::string _port;
        Message _recvBuffer{};

        static void stopServices()
        {
            _Instance._outgoingService.join();
            _Instance._incomingService.join();
        }

        /**
         * Handle the received message by pushing it into the `Client::_receivedMessages`
         * queue or by printing the error
         */
        void handleReceive(const std::error_code &error, std::size_t bytesTransferred)
        {
            if (!error) {
                try {
                    auto message = Message(_recvBuffer);
                    if (!message.empty()) {
                        _receivedMessages.push(message);
                    }
                } catch (const std::exception &e) {
                    std::cerr << e.what() << '\n';
                }
            }
            startReceive();
        }

        /**
         * Receive the next incoming message and push it into the `Client::_receivedMessages` queue
         */
        void startReceive()
        {
            udp::endpoint senderEndpoint;

            _recvBuffer.fill(0);
            _socket.async_receive_from(boost::asio::buffer(_recvBuffer), senderEndpoint,
                [this](std::error_code ec, std::size_t bytesRecvd) { this->handleReceive(ec, bytesRecvd); });
        }

        /**
         * Run the ioService and send incoming messages to locked queue for handling
         */
        void receiveIncoming()
        {
            while (!_Instance._socket.is_open())
                ;
            startReceive();
            while (!_ioService.stopped()) {
                std::cerr << "Here" << std::endl;
                try {
                    _ioService.run();
                } catch (const std::exception &e) {
                    std::cerr << e.what() << '\n';
                }
            }
        }

        void sendOutgoing()
        {
            while (!_Instance._socket.is_open())
                ;
            while (!_ioService.stopped()) {
                if (!_outgoingMessages.empty()) {
                    Message msg = _outgoingMessages.pop();
                    _socket.async_send_to(boost::asio::buffer(msg, msg.size()), _endpoint,
                        [](const boost::system::error_code &ec, std::size_t bytes) {
                            if (ec)
                                std::cerr << "Error while sending message: " << ec.message() << std::endl;
                        });
                }
            }
        };
        /**
         * Static instance of the Client class, lazy loaded
         */
        static Client _Instance;
    };
} // namespace network
