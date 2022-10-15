/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** NetworkClient
*/

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include "LockedQueue.hpp"

using boost::asio::ip::udp;

namespace network
{
    class Client {
      public:
        ~Client()
        {
            _Instance._socket.close();
            _Instance._ioService.stop();
        }

        static Message receive(void)
        {
            Message msg;
            _Instance._socket.receive_from(boost::asio::buffer(msg, msg.size()), _Instance._endpoint);
            return msg;
        }

        static inline void setHost(const std::string &host) { _Instance._host = host; }

        static void setPort(const std::string &port) { _Instance._port = port; }

        static inline void connect(void)
        {
            udp::resolver resolver(_Instance._ioService);
            udp::resolver::query query(udp::v4(), _Instance._host, _Instance._port);
            _Instance._endpoint = *resolver.resolve(query);
            _Instance._socket.open(udp::v4());
        }

        static inline LockedQueue<Message> &getOutgoingMessages() { return _Instance._outgoingMessages; }

        static inline LockedQueue<Message> &getIncomingMessages() { return _Instance._incomingMessages; }

      private:
        Client()
            : _socket(_ioService), _serviceThread(&Client::runService, this),
              _outgoingThread(&Client::sendOutgoing, this)
        {
        }
        boost::asio::io_service _ioService;
        udp::socket _socket;
        Message _recvBuffer;
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
        LockedQueue<Message> _incomingMessages;

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
                        _incomingMessages.push(message);
                        std::cerr << "Sending message :"; // Debug print
                        for (auto &c : message)           //
                            std::cerr << '\\' << (int)c;  //
                        std::cerr << std::endl;           //
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
        void runService()
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
                    std::cerr << "Sending message :"; // Debug print
                    for (auto &c : msg)               //
                        std::cerr << '\\' << (int)c;  //
                    std::cerr << std::endl;           //
                    _socket.send_to(boost::asio::buffer(msg), _endpoint);
                }
            }
        }

        /**
         * Threads used by the client class
         */
        std::thread _serviceThread;
        std::thread _outgoingThread;

        static Client _Instance;
    };
} // namespace network