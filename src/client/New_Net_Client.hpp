/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** New_Net_Client
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
    class New_Net_Client {
      public:
        /**
         * Default destructor of the Client Class
         */
        ~New_Net_Client()
        {
            _Instance._ioService.stop();
            _Instance._socket.close();
            _Instance._outgoingThread.join();
            _Instance._incomingThread.join();
        }

        static inline LockedQueue<Message> &getOutgoingMessages() { return _Instance._outgoingMessages; }

        static inline LockedQueue<Message> &getReceivedMessages() { return _Instance._receivedMessages; }

      private:
        /**
         * Service threads for managing incoming & outgoing messages, using the `Client::_outgoingMessages` &
         * `Client::_receivedMessages queues
         */
        std::thread _outgoingThread;
        std::thread _incomingThread;

        /**
         * Message queues for incoming & outgoing messages
         */
        LockedQueue<Message> _outgoingMessages;
        LockedQueue<Message> _receivedMessages;

        /**
         * Boost Asio service & socket
         */
        bool _started;
        boost::asio::io_service &_ioServiceReceive;
        udp::socket &_socketReceive;
        udp::endpoint &_endpointReceive;
        boost::asio::io_service &_ioServiceSend;
        udp::socket &_socketSend;
        udp::endpoint &_endpointSend;
        std::string _host;
        std::string _port;
        Message _recvbuffer{};

        /**
         * Static instance of the Client class, lazy loaded
         */
        static New_Net_Client _Instance;

        /**
         * Static methods used to connect to the given server (host, port) using udp::v4
         */
        static void connect()
        {
            _Instance._ioServiceReceive = boost::asio::io_service();
            _Instance._ioServiceSend = boost::asio::io_service();
            _Instance._socketReceive = udp::socket(_Instance._ioServiceReceive, udp::endpoint(udp::v4(), 0));
            _Instance._socketSend = udp::socket(_Instance._ioServiceSend, udp::endpoint(udp::v4(), 0));
            udp::resolver resolverReceive = udp::resolver(_Instance._ioServiceReceive);
            udp::resolver resolverSend = udp::resolver(_Instance._ioServiceSend);
            _Instance._endpointReceive = *resolverReceive.resolve({udp::v4(), _Instance._host, _Instance._port});
            _Instance._endpointSend = *resolverSend.resolve({udp::v4(), _Instance._host, _Instance._port});
            _Instance._started = true;
        }

        /**
         * Static methods used to disconnect from the given server (host, port) using udp::v4
         */
        static void disconnect()
        {
            _Instance._socket.close();
            _Instance._outgoingThread.join();
            _Instance._serviceThread.join();
        }

        /**
         * Start the service threads for managing incoming & outgoing messages
         */
        static void startNetServices()
        {
            // _Instance._outgoingThread = std::thread(&New_Net_Client::outgoingService, &_Instance);
            _Instance._incomingThread = std::thread(&New_Net_Client::receiveIncoming, &_Instance);
        }

        void receiveIncoming()
        {
            std::function<void()> receive = [&]() {
                _socket.async_receive_from(boost::asio::buffer(_recvbuffer, _recvbuffer.size()), _endpoint,
                    [](const boost::system::error_code &ec, std::size_t bytes) {
                        if (ec)
                            std::cerr << "Error while receiving message: " << ec.message() << std::endl;
                        else
                            _Instance._receivedMessages.push(_Instance._recvbuffer);
                    });
            };
            while (!_socket.is_open())
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            receive();
            while (!_ioServiceReceive.stopped()) {
                ioService.run();
            }
        }

        /**
         * Private default constructor of the Client Class
         */
        //			New_Net_Client() : _socket(_ioService),

        void sendOutgoind()
        {
            std::function<void()> send = [&]() {
                if (!_outgoingMessages.empty()) {
                    Message msg = _outgoingMessages.pop();
                    _socket.async_send_to(boost::asio::buffer(msg, msg.size()), _endpoint,
                        [](const boost::system::error_code &ec, std::size_t bytes) {
                            if (ec)
                                std::cerr << "Error while sending message: " << ec.message() << std::endl;
                        });
                }
            };
            send();
            while (!_socket.is_open())
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            while (!_ioServiceSend.stopped()) {
                _ioServiceSend.run();
            }
        }

        //			/**
        //			 * Read in the buffer of the instance to get the message to read
        //			 */
        //			static Message receive()
        //			{
        //				Message msg;
        //				_Instance._socket.receive_from(boost::asio::buffer(msg, msg.size()), _Instance._endpoint);
        //				return msg;
        //			}
        //
        //			/**
        //			 * Getters & Setters of client Class
        //			 */
        //			static inline void setHost(const std::string &host) { _Instance._host = host; }
        //
        //			static void setPort(const std::string &port) { _Instance._port = port; }
        //
        //
        //
    };

} // namespace network
