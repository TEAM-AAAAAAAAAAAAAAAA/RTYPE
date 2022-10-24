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
    class Server {
      public:
        /**
         * Destroy the Server object and join all thread pools
         */
        ~Server();

        /**
         * This function allows us to check if the server has received messages
         *@return true if there are messages
         */
        static bool hasMessages();

        /**
         * This function sends a message to a client determined by his ID
         * @param message the message to send
         * @param clientID the ID of the client
         */
        static void sendToClient(const Message &message, uint32_t clientID);

        /**
         * Send a message to all clients that have connected to the server
         *@param message the message to send
         */
        static void sendToAll(const Message &message);

        /**
         * Get the amount of clients that are connected
         * @return Amount of connected clients
         */
        static size_t getClientCount();

        /**
         * Get the ID of client from the clients array
         * @param index the index for the array
         * @return client ID of client n
         */
        static uint32_t getClientIdByIndex(size_t index);

        static LockedQueue<ServerMessage> &getOutgoingMessages();

        static LockedQueue<ClientMessage> &getIncomingMessages();

      private:
        /**
         * Locked queue of all unprocessed incoming messages
         */
        LockedQueue<ServerMessage> _outgoingMessages;

        /**
         * All network related variables
         */
        boost::asio::io_service _ioService;
        udp::endpoint _serverEndpoint;
        udp::endpoint _remoteEndpoint;
        Message _recvBuffer;
        udp::socket _socket;

        /**
         * Threads used by the server class
         */
        std::thread _serviceThread;
        std::thread _outgoingThread;

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
        void handleRemoteError(const std::error_code errorCode, const udp::endpoint& endpoint);

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
        void handleSend(Message message, const std::error_code &error, std::size_t bytesTransferred) {}

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
        void send(const Message &message, udp::endpoint target);

        /**
         * Interpret incoming messages
         */
        void interpretIncoming();

        /**
         * Send messages in the outgoing message queue
         */
        [[noreturn]] void sendOutgoing();

        /**
         *  Clients of the server
         */
        ClientList _clients;
        int _nextClientID;

        /**
         * Constructor which runs a thread for handling server inputs
         * @param localPort the port on which the server runs
         */
        Server(unsigned short localPort = 8000);

        static Server _Instance;
    };
} // namespace network