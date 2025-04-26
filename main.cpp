#include "./server/Server.h"
#include "./client/Client.h"
#include <iostream>
#include <thread>


int main(int __argc, char* __argv[])
{
    // Initialize server
    Server server;
    server.start();


    // Give server a moment to start

    // Initialize client
    Client client;
    //std::this_thread::sleep_for(std::chrono::seconds(1));

    // Connect to server
    client.connect(server.getIPAddress(), server.getPort());
    if (client.isConnected) {
	    server.sendMessage("Hello from server!\n");
        // Send a test message
        client.sendMessage("whats up?\n");
		
		client.receiveMessage();


        // Receive messages (would need proper threading in real application)
        client.receiveMessage();
    }
    // Cleanup
    client.disconnect();
    server.stop();

    return 0;
}