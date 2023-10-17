#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

int main() {
    int server_socket, client_socket;
    char server_message[256] = "Hello from server!";
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_length = sizeof(client_address);

    // Creating the server socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Error creating server socket");
        exit(1);
    }

    // Configure the server address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002); // Port number
    server_address.sin_addr.s_addr = INADDR_ANY; // Bind to any available network interface

    // Binding the socket to the server address
    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("Error binding server socket");
        exit(1);
    }

    // Listening for incoming connections
    if (listen(server_socket, 5) == 0) {
        printf("Listening for client connections...\n");
    } else {
        perror("Error listening for client connections");
        exit(1);
    }

    // Accepting a connection from the client
    client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_length);
    if (client_socket < 0) {
        perror("Error accepting client connection");
        exit(1);
    }

    // Sending data to the client
    send(client_socket, server_message, sizeof(server_message), 0);

    // Close the sockets
    close(client_socket);
    close(server_socket);

    return 0;
}
