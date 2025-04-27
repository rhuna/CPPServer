#include "Server.h"
#include <thread>



//public
Server::Server() 
	: m_port(53000), m_isRunning(false), m_serverIpAddress(sf::IpAddress::LocalHost),
	m_clientIpAddress(sf::IpAddress::Any)
{
	
	m_listener.setBlocking(false); // Set the listener to non-blocking mode

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

			// Start a thread to accept clients
			//std::lock_guard<std::mutex> lock(m_clientMutex);
			acceptThread = std::thread(&Server::acceptConnections, this);
		}
	};
};

void Server::acceptConnections() {
	while (m_isRunning) {
		sf::TcpSocket* clientSocket = new sf::TcpSocket;
		clientSocket->setBlocking(false); // Set the client socket to non-blocking mode
		
		if (m_listener.accept(*clientSocket) != sf::Socket::Status::Done) {
			// No new client connected
			delete clientSocket; // Clean up the socket if not accepted
			std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Sleep to avoid busy waiting
		}
		else {
			std::cout << "accepting connections...\n";
			std::lock_guard<std::mutex> lock(m_clientMutex); // Lock the mutex to protect shared resources
			std::cout << "New client connected to Server IP: " << *clientSocket->getRemoteAddress() << "\n";
			// Store the client socket
			m_clientSockets.push_back(clientSocket);
			// Start a thread to handle this client
			std::thread(&Server::handleClient, this, clientSocket).detach();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void Server::handleClient(sf::TcpSocket* clientSocket) {
	// Handle client communication
	while (m_isRunning) {
		std::cout << "handling client..." << std::endl;
		sf::Packet packet;
		if (clientSocket->receive(packet) == sf::Socket::Status::Done) {
			std::string message;
			packet >> message;
			std::cout << "Message from client: " << message << std::endl;
			processMessage(message);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	// Cleanup
	std::lock_guard<std::mutex> lock(m_clientMutex);
	clientSocket->disconnect();
	auto it = std::find(m_clientSockets.begin(), m_clientSockets.end(), clientSocket);
	if (it != m_clientSockets.end()) {
		m_clientSockets.erase(it);
	}
	delete clientSocket;
};
void Server::stop() {
	// Stop the server
	if (m_isRunning) {
		// Close all client connections and cleanup
		m_isRunning = false;
		if (acceptThread.joinable()) {
			acceptThread.join();  // Wait for thread to finish
		}
		std::cout << "Server stopped." << std::endl;
		cleanup();
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
	std::lock_guard<std::mutex> lock(m_clientMutex); // Lock the mutex to protect shared resources
	m_packet << message;

	for (auto it = m_clientSockets.begin(); it != m_clientSockets.end(); ) {
		sf::TcpSocket* client = *it;
		if (client->send(m_packet) != sf::Socket::Status::Done) {
			std::cerr << "Failed to send message to client." << std::endl;
			// Remove disconnected clients
			client->disconnect();
			it = m_clientSockets.erase(it);
			delete client;
		}
		else {
			std::cout << "Message sent from server: " << message << std::endl;
			++it;
		}
	}

};
void Server::receiveMessage() {
	// Receive a message from the client
	if (m_isRunning) {
		sf::Packet packet;
		if (m_clientSocket.receive(packet) == sf::Socket::Status::Done) {
			std::string message;
			packet >> message;
			std::cout << "Message received from Server: " << message << std::endl;
			processMessage(message);
		}
		else {
			std::cerr << "Server Failed to receive message." << std::endl;
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
			std::cout << "Client connected to server." << std::endl;
			// You can store the socket for further communication
		}
		else {
			std::cerr << "Server Failed to accept client connection." << std::endl;
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
	// Cleanup client connections
	for (auto socket : m_clientSockets) {
		socket->disconnect();
		delete socket;
	}
	m_clientSockets.clear();

	// Close listener
	m_listener.close();

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