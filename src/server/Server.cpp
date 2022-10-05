#include "Server.hpp"

namespace Network {
	Server::Server(unsigned short localPort) :
		socket(_ioService, udp::endpoint(udp::v4(), localPort)),
		_serviceThread(&Server::runService, this),
		nextClientID(0L),
		_interpretPool(6)
	{
    	boost::asio::post(_interpretPool, boost::bind(&Server::interpretIncoming, this));
		std::cerr << "Starting server on port " <<  localPort << std::endl;
	};

	Server::~Server()
	{
		_ioService.stop();
		_serviceThread.join();
	}

	void Server::startReceive()
	{
		socket.async_receive_from(boost::asio::buffer(_recvBuffer), _remoteEndpoint,
			[this](std::error_code ec, std::size_t bytesRecvd){ this->handleReceive(ec, bytesRecvd); });
	}

	void Server::handleRemoteError(const std::error_code errorCode, const udp::endpoint endpoint)
	{
		bool found = false;
		int32_t id;
		for (const auto& client : clients)
			if (client.second == endpoint) {
				found = true;
				id = client.first;
				break;
			}
		if (found == false)
			return;
		clients.erase(id);
	}

	void Server::handleReceive(const std::error_code& error, std::size_t bytesTransferred)
	{
		if (!error)
		{
			try {
				auto message = ClientMessage(std::string(_recvBuffer.data(), _recvBuffer.data() + bytesTransferred), getOrCreateClientID(_remoteEndpoint));
				if (!message.first.empty())
					_incomingMessages.push(message);
			}
			catch (std::exception ex) {
				std::cerr << "handleReceive: Error parsing incoming message:" << ex.what() << std::endl;
			}
			catch (...) {
				std::cerr << "handleReceive: Unknown error while parsing incoming message" << std::endl;;
			}
		}
		else
		{
			std::cerr << "handleReceive: error: " << error.message() << " while receiving from address " << _remoteEndpoint << std::endl;
			handleRemoteError(error, _remoteEndpoint);
		}

		startReceive();
	}

	void Server::send(const std::string& message, udp::endpoint endpoint)
	{
		socket.send_to(boost::asio::buffer(message), endpoint);
	}

	void Server::runService()
	{
		startReceive();
		while (!_ioService.stopped()){
			try {
				_ioService.run();
			}
			catch (const std::exception& e) {
				std::cerr << "Server: Network exception: " << e.what() << std::endl;
			}
			catch (...) {
				std::cerr << "Server: Network exception: unknown" << std::endl;
			}
		}
		std::cerr << "Server network thread stopped" << std::endl;
	};

	int32_t Server::getOrCreateClientID(udp::endpoint endpoint)
	{
		for (const auto& client : clients)
			if (client.second == endpoint)
				return client.first;

		auto id = ++nextClientID;
		clients.insert(Client(id, endpoint));
		return id;
	};

	void Server::sendToClient(const std::string& message, uint32_t clientID)
	{
		try {
			send(message, clients.at(clientID));
		}
		catch (std::out_of_range) {
			std::cerr << "sendToClient : Unknown client ID " << clientID << std::endl;
		}
	};

	void Server::sendToAll(const std::string& message)
	{
		for (auto client : clients)
			send(message, client.second);
	}

	void Server::interpretIncoming(void)
	{
		Network::ClientMessage message;
		while (1) {
			if (!_incomingMessages.empty())
				message = _incomingMessages.pop();
		    	boost::asio::post(_interpretPool, boost::bind(&Server::interpretIncoming, this));
				// Deserialize and add as task
		}
	}

	size_t Server::getClientCount()
	{
		return clients.size();
	}

	uint32_t Server::getClientIdByIndex(size_t index)
	{
		auto it = clients.begin();
		for (int i = 0; i < index; i++)
			++it;
		return it->first;
	};

	bool Server::hasMessages()
	{
		return !_incomingMessages.empty();
	};
}