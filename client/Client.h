#ifndef CLIENT_H
#define CLIENT_H
#include <iostream>
#include <SFML/Network.hpp>

class Client{
public:	
	Client();
	Client(sf::IpAddress servIPadd);
	~Client();
	void connect(const sf::IpAddress& ipAddress, unsigned short port);
	void disconnect();
	void sendMessage(const std::string& message);
	void receiveMessage();
	void handleServerResponse(const std::string& response);
	void status();

private:
	sf::TcpSocket socket;
	bool isConnected;
	sf::IpAddress serverIpAddress;
	unsigned short serverPort;
	// Add any other necessary member variables or methods here
	void initialize();
	void cleanup();
	void processMessage(const std::string& message);

};



#endif // !CLIENT_H


