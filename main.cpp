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
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Initialize client
    Client client;

    // Connect to server
    client.connect(server.getIPAddress(), server.getPort());

    if (client.isConnected) {
        // Send a test message
        client.sendMessage("whats up?\n");

        // Receive messages (would need proper threading in real application)
        client.receiveMessage();
    }

    // Cleanup
    client.disconnect();
    server.stop();

    return 0;
}