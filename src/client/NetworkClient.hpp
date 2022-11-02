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
#include "LockedQueue.hpp"

using boost::asio::ip::udp;

static boost::asio::io_service service;

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
            _Instance._socket.close();
            _Instance._messageSendingThread.join();
            _Instance._ioServiceThread.join();
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
        static inline void connect()
        {
            udp::resolver resolver(_Instance._ioService);
            udp::resolver::query query(udp::v4(), _Instance._host, _Instance._port);
            _Instance._endpoint = *resolver.resolve(query);
            _Instance._socket.open(udp::v4());
            _Instance.isServiceStarted = true;
        }

        bool isServiceStarted;

      private:
        /**
         * Private default constructor of the Client Class
         */
        Client()
            : isServiceStarted(false), _ioService(service), _ioServiceThread(&Client::runService, this),
              _socket(_ioService), _messageSendingThread(&Client::sendOutgoing, this)
        {
        }

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
        void runService()
        {
            while (isServiceStarted == false)
                ;
            startReceive();
            while (!_ioService.stopped()) {
                try {
                    _ioService.run();
                } catch (const std::exception &e) {
                    std::cerr << e.what() << '\n';
                }
            }
        }

        /**
         * Send messages in the outgoing message queue
         */
        void sendOutgoing()
        {
            while (isServiceStarted == false)
                ;
            while (!_ioService.stopped()) {
                if (!_outgoingMessages.empty()) {
                    auto msg = _outgoingMessages.pop();
                    _socket.async_send_to(
                        boost::asio::buffer(msg), _endpoint, [this](std::error_code ec, std::size_t bytesSent) {});
                }
            }
        }

        /**
         * Locked queue of all unsent outgoing messages
         */
        LockedQueue<Message> _outgoingMessages;

        /**
         * Locked queue of all unprocessed incoming messages
         */
        LockedQueue<Message> _receivedMessages;

        /**
         * Boost Asio service & socket and endpoint
         */
        boost::asio::io_service &_ioService;
        udp::socket _socket;
        udp::endpoint _endpoint;

        /**
         * Server reception buffer
         */
        Message _recvBuffer{};

        /**
         * Server host & port
         */
        std::string _host;
        std::string _port;

        /**
         * Threads used by the client class
         */
        std::thread _ioServiceThread;
        std::thread _messageSendingThread;

        static Client _Instance;
    };
} // namespace network