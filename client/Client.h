#ifndef CLIENT_H
#define CLIENT_H
#include <iostream>
#include <SFML/Network.hpp>
#include <thread>

class Client{
public:	
	
	
	bool isConnected;



	Client();
	Client(sf::IpAddress servIPadd);
	~Client();
	void connect(const sf::IpAddress& ipAddress, unsigned short port);
	void disconnect();
	void sendMessage(const std::string& message);
	void receiveMessage();
	void handleServerResponse(const std::string& response);
	void status();
	void initialize();
	void cleanup();
	void processMessage(const std::string& message);


private:

	sf::Packet m_packet;
	std::vector<sf::Packet> m_packets;
	sf::TcpSocket m_socket;
	sf::IpAddress m_serverIpAddress;
	unsigned short m_serverPort;
	// Add any other necessary member variables or methods here


};



#endif // !CLIENT_H


