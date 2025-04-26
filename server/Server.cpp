#include "Server.h"
#include <thread>



//public
Server::Server() 
	: m_port(53000), m_isRunning(false), m_serverIpAddress(sf::IpAddress::LocalHost),
	m_clientIpAddress(sf::IpAddress::Any)
{
	


};
Server::~Server() {
	// Cleanup code here
	if (m_isRunning) {
		stop();
	}
	std::cout << "Server stopped." << std::endl;
};
sf::IpAddress Server::getIPAddress() {

	// Return the server's IP address
	return m_serverIpAddress;
};
unsigned short Server::getPort() const {
	// Return the server's port
	return m_port;
};
void Server::start() {
	// Start the server
	if (!m_isRunning) {
		if (m_listener.listen(m_port) != sf::Socket::Status::Done) {
			std::cerr << "Failed to start server on port " << m_port << std::endl;
		}
		else {
			std::cout << "Server started on port " << m_port << std::endl;
			m_isRunning = true;
		}
	}
	else {
		std::cout << "Server is already running." << std::endl;
	}
	if (!m_isRunning) {
		if (m_listener.listen(m_port) != sf::Socket::Status::Done) {
			std::cerr << "Failed to start server on port " << m_port << std::endl;
		}
		else {
			std::cout << "Server started on port " << m_port << std::endl;
			m_isRunning = true;

			// Start a thread to accept clients
			acceptThread = std::thread(&Server::acceptConnections, this);
		}
	};
};

void Server::acceptConnections() {
	while (m_isRunning) {
		sf::TcpSocket* clientSocket = new sf::TcpSocket;
		m_clientSocket = clientSocket;
		if (m_listener.accept(*m_clientSocket) == sf::Socket::Status::Done) {
			std::cout << "New client connected: " << *m_clientSocket->getRemoteAddress() << std::endl;
			// Store the client socket
			m_clientSockets.push_back(clientSocket);
			// Start a thread to handle this client
			std::thread(&Server::handleClient, this, clientSocket).detach();
		}
	}
}

void Server::handleClient(sf::TcpSocket* clientSocket) {
	// Handle client communication
	while (m_isRunning) {
		sf::Packet packet;
		if (clientSocket->receive(packet) == sf::Socket::Status::Done) {
			std::string message;
			packet >> message;
			std::cout << "Message received from client: " << message << std::endl;
			processMessage(message);
		}
		else {
			std::cerr << "Failed to receive message from client." << std::endl;
			break;
		}

	}
	clientSocket->disconnect();
	delete clientSocket;
};
void Server::stop() {
	// Stop the server
	if (m_isRunning) {
		// Close all client connections and cleanup
		cleanup();
		m_isRunning = false;
		std::cout << "Server stopped." << std::endl;
	}
	else {
		std::cout << "Server is not running." << std::endl;
	}
};
void Server::restart() {
	// Restart the server
	if (m_isRunning) {
		stop();
		start();
		std::cout << "Server restarted." << std::endl;
	}
	else {
		std::cout << "Server is not running." << std::endl;
	}
};
void Server::status() {
	// Print server status
	if (m_isRunning) {
		std::cout << "Server is running on port " << m_port << std::endl;
	}
	else {
		std::cout << "Server is not running." << std::endl;
	}
};
void Server::sendMessage(const std::string& message) {
	// Send a message to the client
	if (m_isRunning) {
		m_packet << message;
		if (m_clientSocket.send(m_packet) != sf::Socket::Status::Done) {
			std::cerr << "Failed to send message." << std::endl;
		}
		else {
			std::cout << "Message sent: " << message << std::endl;
		}
	}
	else {
		std::cerr << "Server is not running." << std::endl;
	}
};
void Server::receiveMessage() {
	// Receive a message from the client
	if (m_isRunning) {
		if (m_clientSocket.receive(m_packet) == sf::Socket::Status::Done) {
			std::string message;
			m_packet >> message;
			std::cout << "Message received: " << message << std::endl;
			processMessage(message);
		}
		else {
			std::cerr << "Failed to receive message." << std::endl;
		}
	}
	else {
		std::cerr << "Server is not running." << std::endl;
	}
};
void Server::handleClientConnection() {
	
	// Handle client connection
	if (m_isRunning) {
		if (m_clientSocket.isBlocking() == true) {
			std::cout << "Client connected." << std::endl;
			// You can store the socket for further communication
		}
		else {
			std::cerr << "Failed to accept client connection." << std::endl;
		}
	}
	else {
		std::cerr << "Server is not running." << std::endl;
	}
};
void Server::handleClientDisconnection() {
	// Handle client disconnection
	if (m_isRunning) {
		m_clientSocket.disconnect();
		std::cout << "Client disconnected." << std::endl;
	}
	else {
		std::cerr << "Server is not running." << std::endl;
	}
};
void Server::handleClientMessage(const std::string& message) {
	// Handle client message
	if (m_isRunning) {
		std::cout << "Client message: " << message << std::endl;
		// Process the message as needed
		processMessage(message);
	}
	else {
		std::cerr << "Server is not running." << std::endl;
	}
};



//private
void Server::initialize() {
	
};
void Server::cleanup() {
	// Cleanup code here
	std::cout << "Server cleanup completed." << std::endl;
	// Close all client connections and free resources
	// You can also reset any member variables if needed
};
void Server::acceptClient() {
	// Accept a client connection

	if (m_clientSocket.isBlocking() == true) {
		std::cout << "Client accepted." << std::endl;
		// You can store the socket for further communication
	}
	else {
		std::cerr << "Failed to accept client." << std::endl;
	}
};
void Server::closeClient() {
	
};
void Server::processMessage(const std::string& message) {
	// Process the received message
	std::cout << "Processing message: " << message << std::endl;
	// You can implement your message processing logic here
	// For example, you can parse the message and take appropriate actions
};