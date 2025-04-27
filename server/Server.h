#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <thread>
#include <mutex>


class Server{

public:

	std::thread acceptThread; 
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
	void initialize();
	void cleanup();
	void acceptClient();
	void closeClient();
	void processMessage(const std::string& message);
	void acceptConnections();
	void handleClient(sf::TcpSocket* clientSocket);
	

private:


	std::mutex m_clientMutex;
	std::vector<sf::Packet> m_packets;
	std::vector<sf::TcpSocket*> m_clientSockets;
	sf::Packet m_packet;
	sf::TcpSocket m_clientSocket;
	sf::TcpListener m_listener;
	unsigned short m_port;
	std::string m_ipAddress;
	bool m_isRunning;
	sf::IpAddress m_serverIpAddress;
	sf::IpAddress m_clientIpAddress;
	// Add any other necessary member variables or methods here
	
};



#endif // !SERVER_H

