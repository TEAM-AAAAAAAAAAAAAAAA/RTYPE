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
            _Instance._outgoingService.join();
            _Instance._incomingService.join();
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
        static inline void connect()
        {
            udp::resolver resolver(_Instance._ioService);
            udp::resolver::query query(udp::v4(), _Instance._host, _Instance._port);
            _Instance._endpoint = *resolver.resolve(query);
            _Instance._socket.open(udp::v4());
        }

      private:
        /**
         * Private default constructor of the Client Class
         */
        Client() : _socket(_ioService), _incomingService(&Client::receiveIncoming, this),
              _outgoingService(&Client::sendOutgoing, this) {}

        /**
         * Boost Asio service & socket
         */
        boost::asio::io_service _ioService;
        udp::socket _socket;
        Message _recvBuffer{};
        udp::endpoint _endpoint;
        std::string _host;
        std::string _port;

        /**
         * Locked queue of all unsent outgoing messages
         */
        LockedQueue<Message> _outgoingMessages;

        /**
         * Locked queue of all unprocessed incoming messages
         */
        LockedQueue<Message> _receivedMessages;

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
         * Handles the sending of packets
         * @param message the packet as an array
         * @param error error code of sending
         * @param bytesTransferred the size of the outgoing packet
         */
        void handleSend(Message message, const std::error_code &error, std::size_t bytesTransferred) {}

        /**
         * Run the client's service
         */
        void receiveIncoming()
        {
            while (!_socket.is_open())
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
            while (!_socket.is_open())
                ;
            while (!_ioService.stopped()) {
                if (!_outgoingMessages.empty()) {
                    auto msg = _outgoingMessages.pop();
                    _socket.async_send_to(boost::asio::buffer(msg), _endpoint, [](const boost::system::error_code &ec, std::size_t bytes){});
                }
            }
        }

        /**
         * Threads used by the client class
         */
        std::thread _incomingService;
        std::thread _outgoingService;

        static Client _Instance;
    };
} // namespace network