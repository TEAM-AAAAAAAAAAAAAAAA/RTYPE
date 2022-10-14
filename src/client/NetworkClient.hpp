/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** NetworkClient
*/

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include "server/LockedQueue.hpp"
#include "server/Server.hpp"

using boost::asio::ip::udp;

namespace network
{
    class Client {
      public:
        Client(boost::asio::io_service &ioService, const std::string &host, const std::string &port)
            : _ioService(ioService), _serviceThread(&Client::runService, this), _outgoingThread(&Client::sendOutgoing, this), _socket(ioService, udp::endpoint(udp::v4(), 0))
        {
            udp::resolver resolver(_ioService);
            udp::resolver::query query(udp::v4(), host, port);
            udp::resolver::iterator iter = resolver.resolve(query);
            _endpoint = *iter;
        }

        ~Client()
        {
            _socket.close();
            _ioService.stop();
        }

        std::array<char, 10> receive(void)
        {
            std::array<char, 10> msg;
            _socket.receive_from(boost::asio::buffer(msg, msg.size()), _endpoint);
            return msg;
        }

        /**
         * Locked queue of all unsent outgoing messages
         */
        LockedQueue<std::array<char, 10>> outgoingMessages;

        /**
         * Locked queue of all unprocessed incoming messages
         */
        LockedQueue<std::array<char, 10>> incomingMessages;

      private:
        /**
         * All network related variables
         */
        boost::asio::io_service &_ioService;
        udp::socket _socket;
        std::array<char, 10> _recvBuffer;
        udp::endpoint _endpoint;

        /**
         * Handles the incoming messages by placing them into the incoming
         * messages locked queue
         * @param error error of reception
         * @param bytesTransferred the size of the incoming packet
         */
        void handleReceive(const std::error_code &error, std::size_t bytesTransferred)
        {

        }

        /**
         * Handles the sending of packets
         * @param message the packet as an array
         * @param error error code of sending
         * @param bytesTransferred the size of the outgoing packet
         */
        void handleSend(std::array<char, 10> message, const std::error_code &error, std::size_t bytesTransferred) {}

        /**
         * Sends a message to the server
         *@param msg the message being sent
         */
        void send(const std::array<char, 10> &msg) { _socket.send_to(boost::asio::buffer(msg, msg.size()), _endpoint); }

        /**
         * Run the client's service
         */
        void runService();

        /**
         * Send messages in the outgoing message queue
         */
        void sendOutgoing();

        /**
         * Threads used by the client class
         */
        std::thread _serviceThread;
        std::thread _outgoingThread;
    };
} // namespace network