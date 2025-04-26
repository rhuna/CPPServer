#include "Client.h"
#include <iostream>
#include <optional>


Client::Client() 
	: isConnected(false), serverPort(53000), serverIpAddress(sf::IpAddress::LocalHost), 
	socket()
{// Initialize the socket
	if (socket.connect(serverIpAddress, serverPort) == sf::Socket::Status::Done) {
		isConnected = true;
		std::cout << "Client connected to server at " << serverIpAddress << ":" << serverPort << std::endl;
	}
	else {
		std::cerr << "client Failed to connect to server at " << serverIpAddress << " : " << serverPort << std::endl;
	}

}
Client::Client(sf::IpAddress servIPadd) 
	: isConnected(false), serverPort(53000), serverIpAddress(servIPadd)
{
	// Initialize the socket
	if (socket.connect(serverIpAddress, serverPort) == sf::Socket::Status::Done) {
		isConnected = true;
		std::cout << "Client connected to server at " << serverIpAddress << ":" << serverPort << std::endl;
	}
	else {
		std::cerr << "client Failed to connect to server at " << serverIpAddress << " : " << serverPort << std::endl;
	}
}
Client::~Client() {
	// Cleanup code here
	if (isConnected) {
		disconnect();
	}
	socket.disconnect();
	std::cout << "Client disconnected." << std::endl;
};
void Client::connect(const sf::IpAddress& ipAddress, unsigned short port) {
	// Connect to the server
	serverIpAddress = ipAddress;
	serverPort = port;
	if (socket.connect(serverIpAddress, serverPort) == sf::Socket::Status::Done) {
		isConnected = true;
		std::cout << "client connected to server at " << serverIpAddress << ":" << serverPort << std::endl;
	}
	else {
		std::cerr << "client Failed to connect to server at " <<serverIpAddress<< " : " << serverPort << std::endl;
	}
};
void Client::disconnect() {
	// Disconnect from the server
	if (isConnected) {
		socket.disconnect();
		isConnected = false;
		std::cout << "Disconnected from server." << std::endl;
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
		if (socket.send(packet) != sf::Socket::Status::Done) {
			std::cerr << "Failed to send message." << std::endl;
		}
		else {
			std::cout << "Message sent: " << message << std::endl;
		}
	}
	else {
		std::cerr << "Client is not connected." << std::endl;
	}
};
void Client::receiveMessage() {
	// Receive a message from the server
	if (isConnected) {
		sf::Packet packet;
		if (socket.receive(packet) == sf::Socket::Status::Done) {
			std::string message;
			packet >> message;
			std::cout << "Message received: " << message << std::endl;
			handleServerResponse(message);
		}
		else {
			std::cerr << "Failed to receive message." << std::endl;
		}
	}
	else {
		std::cerr << "Client is not connected." << std::endl;
	}
};
void Client::handleServerResponse(const std::string& response) {
	// Handle the server's response
	std::cout << "Server response: " << response << std::endl;
	// Process the response as needed
	// For example, you can call processMessage(response);
	// processMessage(response);
};
void Client::status() {

	
};
void Client::initialize() {
	
}; 
void Client::cleanup() {
	
};
void Client::processMessage(const std::string& message) {
	// Process the message received from the server
	std::cout << "Processing message: " << message << std::endl;
	// Add your message processing logic here
};