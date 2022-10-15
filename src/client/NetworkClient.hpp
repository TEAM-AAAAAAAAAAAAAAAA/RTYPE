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
    class Client
    {
    public:
        Client(const std::string &host, const std::string &port)
            : _serviceThread(&Client::runService, this), _outgoingThread(&Client::sendOutgoing, this), _socket(_ioService)
        {
            udp::resolver resolver(_ioService);
            udp::resolver::query query(udp::v4(), host, port);
            _endpoint = *resolver.resolve(query);
            _socket.open(udp::v4());
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
        boost::asio::io_service _ioService;
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
            if (!error)
            {
                try
                {
                    auto message = std::array<char, 10>(_recvBuffer);
                    if (!message.empty())
                    {
                        incomingMessages.push(message);
                        std::cerr << "Sending message :"; // Debug print
                        for (auto &c : outgoingMessages.front()) //
                            std::cerr << '\\' << (int)c; //
                        std::cerr << std::endl; //
                    }
                }
                catch (const std::exception &e)
                {
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
                                       [this](std::error_code ec, std::size_t bytesRecvd)
                                       { this->handleReceive(ec, bytesRecvd); });
        }

        /**
         * Handles the sending of packets
         * @param message the packet as an array
         * @param error error code of sending
         * @param bytesTransferred the size of the outgoing packet
         */
        void handleSend(std::array<char, 10> message, const std::error_code &error, std::size_t bytesTransferred) {}

        /**
         * Run the client's service
         */
        void runService()
        {
            usleep(10000);
            startReceive();
            while (!_ioService.stopped())
            {
                try
                {
                    _ioService.run();
                }
                catch (const std::exception &e)
                {
                    std::cerr << e.what() << '\n';
                }
            }
        }

        /**
         * Send messages in the outgoing message queue
         */
        void sendOutgoing()
        {
            sleep(1);
            while (!_ioService.stopped())
            {
                if (!outgoingMessages.empty())
                {
                    std::cerr << "Sending message :"; // Debug print
                    for (auto &c : outgoingMessages.front()) //
                        std::cerr << '\\' << (int)c; //
                    std::cerr << std::endl; //
                    auto msg = outgoingMessages.pop();
                    _socket.send_to(boost::asio::buffer(msg), _endpoint);
                }
            }
        }

        /**
         * Threads used by the client class
         */
        std::thread _serviceThread;
        std::thread _outgoingThread;
    };
} // namespace network