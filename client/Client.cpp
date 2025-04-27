#include "Client.h"
#include <iostream>
#include <optional>


Client::Client() 
	: isConnected(false), m_serverPort(53000), m_serverIpAddress(sf::IpAddress::LocalHost),
	m_socket()
{// Initialize the socket

	std::cout << "client constructor called" << std::endl;
	m_socket.setBlocking(false); // Set the socket to non-blocking mode
}
Client::Client(sf::IpAddress servIPadd) 
	: isConnected(false), m_serverPort(53000), m_serverIpAddress(servIPadd)
{
	std::cout << "client constructor with IP called" << std::endl;
}
Client::~Client() {
	// Cleanup code here
	if (isConnected) {
		disconnect();
	}
	m_socket.disconnect();
	std::cout << "Client disconnected." << std::endl;
};
void Client::connect(const sf::IpAddress& ipAddress, unsigned short port) {
	// Connect to the server
	std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate some delay for connection
	if (isConnected) {
		std::cerr << "Already connected to server." << std::endl;
		return;
	}

	m_serverIpAddress = ipAddress;
	m_serverPort = port;

	sf::Socket::Status status = m_socket.connect(m_serverIpAddress, m_serverPort, sf::seconds(5));
	if (status == sf::Socket::Status::Done) {
		isConnected = true;
		std::cout << "Connected to server at " << m_serverIpAddress << ":" << m_serverPort << std::endl;
	}
	else {
		std::cerr << "client Failed to connect to server: ";
		switch (status) {
		case sf::Socket::Status::NotReady: std::cerr << "Not ready"; break;
		case sf::Socket::Status::Partial: std::cerr << "Partial"; break;
		case sf::Socket::Status::Disconnected: std::cerr << "Disconnected"; break;
		case sf::Socket::Status::Error: std::cerr << "Error"; break;
		default: std::cerr << "Unknown error"; break;
		}
		std::cerr << std::endl;
	}
};
void Client::disconnect() {
	// Disconnect from the server
	if (isConnected) {
		m_socket.disconnect();
		isConnected = false;
		std::cout << "client Disconnected from server." << std::endl;
	}
	else {
		std::cerr << "Client is not connected." << std::endl;
	}
};
void Client::sendMessage(const std::string& message) {
	// Send a message to the server
	if (isConnected) {
		sf::Packet packet;
		packet << message;
		if (m_socket.send(packet) != sf::Socket::Status::Done) {
			std::cerr << "Client Failed to send message." << std::endl;
		}
		else {
			std::cout << "Message sent from client: " << message << std::endl;
		}
	}
	else {
		std::cerr << "Client is not connected." << std::endl;
	}
	m_packet.clear(); // Clear the packet after sending
};
void Client::receiveMessage() {
	// Receive a message from the server
	if (isConnected) {
		sf::Packet packet;
		if (m_socket.receive(packet) == sf::Socket::Status::Done) {
			std::string message;
			packet >> message;
			
			std::cout << "client Message received: " << message << std::endl;
			handleServerResponse(message);
		}
		else {
			std::cerr << "client Failed to receive message." << std::endl;
		}
	}
	else {
		std::cerr << "Client is not connected." << std::endl;
	}
	m_packet.clear(); // Clear the packet after processing
};
void Client::handleServerResponse(const std::string& response) {
	// Handle the server's response
	std::cout << "handling Server response: " << response << std::endl;
	// Process the response as needed
	// For example, you can call processMessage(response);
	// processMessage(response);
};
void Client::status() {

	
};
void Client::initialize() {
	// Initialization code here
	std::cout << "Client initialized." << std::endl;
	// You can set up the socket and other resources here
	m_socket.setBlocking(false); // Set the socket to non-blocking mode
	// Add any other necessary initialization steps
}; 
void Client::cleanup() {
	// Cleanup code here
	std::cout << "Client cleanup completed." << std::endl;
	// Close the socket and free resources
	m_socket.disconnect();
	isConnected = false;
};
void Client::processMessage(const std::string& message) {
	// Process the message received from the server
	std::cout << "Processing message: " << message << std::endl;
	// Add your message processing logic here
};