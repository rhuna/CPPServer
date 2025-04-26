#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>


class Server{

public:
	Server();
	~Server();	
	void start();
	void stop();
	void restart();
	void status();
	void sendMessage(const std::string& message);
	void receiveMessage();
	void handleClientConnection();
	void handleClientDisconnection();
	void handleClientMessage(const std::string& message);
	sf::IpAddress getIPAddress();
	unsigned short getPort() const;

private:
	unsigned short port;
	std::string ipAddress;
	bool isRunning;
	sf::IpAddress serverIpAddress;
	sf::IpAddress clientIpAddress;
	// Add any other necessary member variables or methods here
	void initialize();
	void cleanup();
	void acceptClient();
	void closeClient();
	void processMessage(const std::string& message);
};



#endif // !SERVER_H

