#include "Server.h"



//public
Server::Server() 
	: port(53000), isRunning(false), serverIpAddress(sf::IpAddress::LocalHost),
	clientIpAddress(sf::IpAddress::Any)
{
	// Initialize the server
	sf::TcpListener listener;
	if (listener.listen(port) != sf::Socket::Status::Done) {
		std::cerr << "Failed to start server on port " << port << std::endl;
	}
	else {
		std::cout << "Server started on port " << port << std::endl;
		isRunning = true;
	}


};
Server::~Server() {
	// Cleanup code here
	if (isRunning) {
		stop();
	}
	std::cout << "Server stopped." << std::endl;
};
sf::IpAddress Server::getIPAddress() {

	// Return the server's IP address
	return serverIpAddress;
};
unsigned short Server::getPort() const {
	// Return the server's port
	return port;
};
void Server::start() {
	// Start the server
	if (!isRunning) {
		sf::TcpListener listener;
		if (listener.listen(port) != sf::Socket::Status::Done) {
			std::cerr << "Failed to start server on port " << port << std::endl;
		}
		else {
			std::cout << "Server started on port " << port << std::endl;
			isRunning = true;
		}
	}
	else {
		std::cout << "Server is already running." << std::endl;
	}
};
void Server::stop() {
	// Stop the server
	if (isRunning) {
		// Close all client connections and cleanup
		cleanup();
		isRunning = false;
		std::cout << "Server stopped." << std::endl;
	}
	else {
		std::cout << "Server is not running." << std::endl;
	}
};
void Server::restart() {
	// Restart the server
	if (isRunning) {
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
	if (isRunning) {
		std::cout << "Server is running on port " << port << std::endl;
	}
	else {
		std::cout << "Server is not running." << std::endl;
	}
};
void Server::sendMessage(const std::string& message) {
	// Send a message to the client
	if (isRunning) {
		sf::TcpSocket socket;
		sf::Packet packet;
		packet << message;
		if (socket.send(packet) != sf::Socket::Status::Done) {
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
	if (isRunning) {
		sf::TcpSocket socket;
		sf::Packet packet;
		if (socket.receive(packet) == sf::Socket::Status::Done) {
			std::string message;
			packet >> message;
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
	if (isRunning) {
		sf::TcpSocket socket;
		if (socket.isBlocking() == true) {
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
	if (isRunning) {
		sf::TcpSocket socket;
		socket.disconnect();
		std::cout << "Client disconnected." << std::endl;
	}
	else {
		std::cerr << "Server is not running." << std::endl;
	}
};
void Server::handleClientMessage(const std::string& message) {
	// Handle client message
	if (isRunning) {
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
	sf::TcpSocket socket;
	if (socket.isBlocking() == true) {
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