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
#include "IServer.hpp"
#include "LockedQueue.hpp"
#include <boost/asio/thread_pool.hpp>
#include <boost/shared_ptr.hpp>

using boost::asio::ip::udp;

typedef std::map<uint32_t, udp::endpoint> ClientList;
typedef ClientList::value_type Client;

/**
 * Server class which is used by the game server to communicate with the client
 */
namespace Network
{
    class Server : public IServer {
      public:
        /**
         * Constructor which runs a thread for handling server inputs
         *@param local_port the port on which the server runs
         */
        explicit Server(unsigned short local_port);

        /**
         * Destroy the Server object and join all thread pools
         */
        virtual ~Server();

        /**
         * This function allows us to check if the server has received messages
         *@return true if there are messages
         */
        bool HasMessages() override;

        /**
         * This function sends a message to a client determined by his ID
         *@param message the message to send
         *@param clientID the ID of the client
         */
        void SendToClient(const std::string &message, uint32_t clientID) override;

        /**
         * Send a message to all clients that have connected to the server
         *@param message the message to send
         */
        void SendToAll(const std::string &message);

        /**
         * Get the amount of clients that are connected
         *@return Amount of connected clients
         */
        size_t GetClientCount() override;

        /**
         * Get the ID of client from the clients array
         *@param n the index for the array
         *@return client ID of client n
         */
        uint32_t GetClientIdByIndex(size_t index) override;

      private:
        /**
         * All network related variables
         */
        boost::asio::io_service io_service;
        udp::socket socket;
        udp::endpoint server_endpoint;
        udp::endpoint remote_endpoint;
        std::array<char, 8> recv_buffer;

        /**
         * Thread pools used by the server class
         */
        std::thread service_thread;
        boost::asio::thread_pool _interpretPool;

        /**
         * Locked queue of all unprocessed incoming messages
         */
        LockedQueue<ClientMessage> incomingMessages;

        /**
         * Starts the reception of messages for the server
         */
        void start_receive();

        /**
         * Handling of error from sending/receiving
         *@param error_code the code of the error being handled
         *@param remote_endpoint the endpoint where the error occured
         */
        void handle_remote_error(const std::error_code error_code, const udp::endpoint remote_endpoint);

        /**
         * Handles the incoming messages by placing them into the incoming
         * messages locked queue
         *@param error error of reception
         *@param bytes_transferred the size of the incoming packet
         */
        void handle_receive(const std::error_code &error, std::size_t bytes_transferred);

        /**
         * Handles the sending of packets
         *@param message the packet as a string
         *@param error error code of sending
         *@param bytes_transferred the size of the outgoing packet
         */
        void handle_send(std::string message, const std::error_code &error, std::size_t bytes_transferred) {}

        /**
         * Run the server's service
         */
        void run_service();

        /**
         *Get the or create client id object
         *@param endpoint endpoint of the client
         *@return int32_t the ID of the client
         */
        int32_t get_or_create_client_id(udp::endpoint endpoint);

        /**
         * Send message to the endpoint
         *@param message message as a string
         *@param target endpoint of the receiving client
         */
        void send(const std::string &message, udp::endpoint target);

        /**
         * Interpret incoming messages
         */
        void interpretIncoming();

        /**
         *  Clients of the server
         */
        ClientList clients;
        int nextClientID;
    };
} // namespace Network