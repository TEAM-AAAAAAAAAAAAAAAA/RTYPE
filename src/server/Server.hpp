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
#include "LockedQueue.hpp"
#include <boost/asio/thread_pool.hpp>
#include <boost/shared_ptr.hpp>

using boost::asio::ip::udp;

typedef std::map<uint32_t, udp::endpoint> ClientList;
typedef ClientList::value_type Client;

/**
 * Server class which is used by the game server to communicate with the client
 */
namespace network
{
    /**
     * Standard pair class that contains a string and the ID of the client that
     * sent it
     */
    typedef std::pair<std::array<char, 10>, unsigned int> ClientMessage;
    typedef std::pair<std::array<char, 10>, std::vector<unsigned int>> ServerMessage;

    class Server {
      public:
        /**
         * Constructor which runs a thread for handling server inputs
         * @param localPort the port on which the server runs
         */
        Server() : Server(8000) {}
        explicit Server(unsigned short localPort);

        /**
         * Destroy the Server object and join all thread pools
         */
        ~Server();

        /**
         * This function allows us to check if the server has received messages
         *@return true if there are messages
         */
        bool hasMessages();

        /**
         * This function sends a message to a client determined by his ID
         * @param message the message to send
         * @param clientID the ID of the client
         */
        void sendToClient(const std::array<char, 10> &message, uint32_t clientID);

        /**
         * Send a message to all clients that have connected to the server
         *@param message the message to send
         */
        void sendToAll(const std::array<char, 10> &message);

        /**
         * Get the amount of clients that are connected
         * @return Amount of connected clients
         */
        size_t getClientCount();

        /**
         * Get the ID of client from the clients array
         * @param index the index for the array
         * @return client ID of client n
         */
        uint32_t getClientIdByIndex(size_t index);

        /**
         * Locked queue of all unprocessed incoming messages
         */
        LockedQueue<ServerMessage> outgoingMessages;

      private:
        /**
         * All network related variables
         */
        boost::asio::io_service _ioService;
        udp::endpoint _serverEndpoint;
        udp::endpoint _remoteEndpoint;
        std::array<char, 10> _recvBuffer;
        udp::socket _socket;

        /**
         * Threads used by the server class
         */
        std::thread _serviceThread;
        std::thread _outgoingThread;
        std::thread _interpretThread;

        /**
         * Locked queue of all unprocessed incoming messages
         */
        LockedQueue<ClientMessage> _incomingMessages;

        /**
         * Starts the reception of messages for the server
         */
        void startReceive();

        /**
         * Handling of error from sending/receiving
         * @param errorCode the code of the error being handled
         * @param remoteEndpoint the endpoint where the error occured
         */
        void handleRemoteError(const std::error_code errorCode, const udp::endpoint endpoint);

        /**
         * Handles the incoming messages by placing them into the incoming
         * messages locked queue
         * @param error error of reception
         * @param bytesTransferred the size of the incoming packet
         */
        void handleReceive(const std::error_code &error, std::size_t bytesTransferred);

        /**
         * Handles the sending of packets
         * @param message the packet as an array
         * @param error error code of sending
         * @param bytesTransferred the size of the outgoing packet
         */
        void handleSend(std::array<char, 10> message, const std::error_code &error, std::size_t bytesTransferred) {}

        /**
         * Run the server's service
         */
        void runService();

        /**
         *Get the or create client id object
         * @param endpoint endpoint of the client
         * @return int32_t the ID of the client
         */
        int32_t getOrCreateClientID(udp::endpoint endpoint);

        /**
         * Send message to the endpoint
         * @param message message as an array
         * @param target endpoint of the receiving client
         */
        void send(const std::array<char, 10> &message, udp::endpoint target);

        /**
         * Interpret incoming messages
         */
        void interpretIncoming();

        /**
         * Send messages in the outgoing message queue
         */
        void sendOutgoing();

        /**
         *  Clients of the server
         */
        ClientList _clients;
        int _nextClientID;
    };
} // namespace network