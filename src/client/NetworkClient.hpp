/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** NetworkClient
*/

#pragma once

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include "Constant.hpp"
#include "LockedQueue.hpp"

using chrono = std::chrono::high_resolution_clock;
using chronoDuration = std::chrono::duration<double, std::milli>;
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
            getInstance()._isStillRunning = false;
            getInstance()._ioService.stop();
            getInstance()._outgoingService.join();
            getInstance()._incomingService.join();
            getInstance()._socket.close();
        }

        /**
         * Getters & Setters of client Class
         */
        static inline void setHost(const std::string &host) { getInstance()._host = host; }

        static void setPort(const std::string &port) { getInstance()._port = port; }

        static inline LockedQueue<Message> &getOutgoingMessages() { return getInstance()._outgoingMessages; }

        static inline LockedQueue<Message> &getReceivedMessages() { return getInstance()._receivedMessages; }

        /**
         * Static methods used to connect to the given server (host, port) using udp::v4
         */
        static inline void connect()
        {
            udp::resolver resolver(getInstance()._ioService);
            getInstance()._socket = udp::socket(getInstance()._ioService);
            udp::resolver::query query(udp::v4(), getInstance()._host, getInstance()._port);
            getInstance()._endpoint = *resolver.resolve(query);
            getInstance()._socket.open(udp::v4());
        }

        static inline void disconnect()
        {
            getInstance()._ioService.stop();
            getInstance()._socket.close();
        }

      private:
        /**
         * Private default constructor of the Client Class
         */
        Client()
            : _socket(_ioService), _incomingService(&Client::receiveIncoming, this),
              _outgoingService(&Client::sendOutgoing, this)
        {
        }

        /**
         * Boost Asio service & socket
         */
        boost::asio::io_service _ioService;
        udp::socket _socket;
        Message _recvBuffer{};
        udp::endpoint _endpoint;
        std::string _host;
        std::string _port;
        bool _isStillRunning = true;

        /**
         * Locked queue of all unsent outgoing messages
         */
        LockedQueue<Message> _outgoingMessages;

        /**
         * Locked queue of all unprocessed incoming messages
         */
        LockedQueue<Message> _receivedMessages;

        /**
         * The timestamp of the last received message
         */
        std::chrono::_V2::system_clock::time_point _lastPing;

        /**
         * Handles the incoming messages by placing them into the incoming
         * messages locked queue
         * @param error error of reception
         * @param bytesTransferred the size of the incoming packet
         */
        void handleReceive(const std::error_code &error, std::size_t bytesTransferred)
        {
            if (!error) {
                try {
                    auto message = Message(_recvBuffer);
                    _lastPing = chrono::now();
                    if (!message.empty()) {
                        _receivedMessages.push(message);
                    }
                } catch (const std::exception &e) {
                    std::cerr << e.what() << '\n';
                }
            }
            startReceive();
        }

        void startReceive()
        {
            udp::endpoint senderEndpoint;

            _recvBuffer.fill(0);
            _socket.async_receive_from(boost::asio::buffer(_recvBuffer), senderEndpoint,
                [this](std::error_code ec, std::size_t bytesRecvd) { this->handleReceive(ec, bytesRecvd); });
        }

        /**
         * Run the client's service
         */
        void receiveIncoming()
        {
            while (_isStillRunning) {
                while (!_socket.is_open())
                    if (!_isStillRunning)
                        return;
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                startReceive();
                while (!_ioService.stopped()) {
                    try {
                        _ioService.run();
                    } catch (const std::exception &e) {
                        std::cerr << e.what() << '\n';
                    }
                }
            }
        }

        /**
         * Send messages in the outgoing message queue
         */
        void sendOutgoing()
        {
            while (_isStillRunning) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                while (!_socket.is_open())
                    if (!_isStillRunning)
                        return;
                while (!_ioService.stopped()) {
                    if (!_outgoingMessages.empty()) {
                        auto msg = _outgoingMessages.pop();
                        _socket.async_send_to(boost::asio::buffer(msg), _endpoint,
                            [](const boost::system::error_code &ec, std::size_t bytes) {});
                    }
                }
            }
        }

        /**
         * Threads used by the client class
         */
        std::thread _incomingService;
        std::thread _outgoingService;

        static Client &getInstance();
        //        static Client getInstance();
    };
} // namespace network