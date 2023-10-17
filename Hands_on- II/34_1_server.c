#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

void handle_client(int client_socket) {
    // Handle the client here (e.g., send/receive data)
    char server_response[256] = "Message from the server!";
    send(client_socket, server_response, sizeof(server_response), 0);
    close(client_socket);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_length = sizeof(client_address);

    // Creating the server socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Error creating server socket");
        exit(1);
    }

    //CONFIGURING
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002); 
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Binding
    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("Error binding server socket");
        exit(1);
    }

    // Listening
    if (listen(server_socket, 5) == 0) {
        printf("Listening for client connections...\n");
    } else {
        perror("Error");
        exit(1);
    }

    while (1) {
        // Accepting
        client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_length);
        if (client_socket < 0) {
            perror("Error");
            exit(1);
        }

        // Creating
        if (fork() == 0) {
            // Child process
            close(server_socket); 
            handle_client(client_socket);
            exit(0); // Child process terminates
        } else {
            // Parent process
            close(client_socket); 
        }
    }

    close(server_socket);

    return 0;
}
