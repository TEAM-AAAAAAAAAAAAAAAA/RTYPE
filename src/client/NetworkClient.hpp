/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** NetworkClient
*/

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::udp;

namespace network
{
    class Client {
      public:
        Client(boost::asio::io_service &io_service, const std::string &host, const std::string &port)
            : io_service_(io_service), socket_(io_service, udp::endpoint(udp::v4(), 0))
        {
            udp::resolver resolver(io_service_);
            udp::resolver::query query(udp::v4(), host, port);
            udp::resolver::iterator iter = resolver.resolve(query);
            endpoint_ = *iter;
        }

        ~Client() { socket_.close(); }

        void send(const std::array<char, 10> &msg) { socket_.send_to(boost::asio::buffer(msg, msg.size()), endpoint_); }

        std::array<char, 10> receive(void)
        {
            std::array<char, 10> msg;
            socket_.receive_from(boost::asio::buffer(msg, msg.size()), endpoint_);
            return msg;
        }

      private:
        boost::asio::io_service &io_service_;
        udp::socket socket_;
        udp::endpoint endpoint_;
    };
} // namespace network