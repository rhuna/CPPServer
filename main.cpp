#include "./server/Server.h"
#include "./client/Client.h"

int main(int __argc, char* __argv[])
{
	//initialize the server
	Server server;
	server.start();
	//server.sendMessage("Hello, Client!");
	//server.receiveMessage();
	//server.handleClientConnection();
	//server.handleClientDisconnection();
	//server.handleClientMessage("Hello, Server!");
	//server.status();
	//server.restart();
	//server.stop();
	//server.cleanup();

	Client client;

	client.connect(server.getIPAddress(), server.getPort());


	std::cout << "Hello World!" << std::endl;
	return 0;
}