#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

int main() {
    int client_socket;
    char server_response[256];
    struct sockaddr_in server_address;

    // Creating the client socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Error creating client socket");
        exit(1);
    }

    // Configuring the server address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002); // Port number
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Connecting to the server
    if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("Error connecting to the server");
        exit(1);
    }

    // Receiving data from the server
    recv(client_socket, server_response, sizeof(server_response), 0);
    printf("Server response: %s\n", server_response);

    // Close the socket
    close(client_socket);

    return 0;
}
