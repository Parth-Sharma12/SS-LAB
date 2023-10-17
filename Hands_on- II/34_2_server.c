#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <pthread.h>

void *handle_client(void *arg) {
    int client_socket = *((int *)arg);
    
    char server_response[256] = "Hello this is server!";
    send(client_socket, server_response, sizeof(server_response), 0);
    close(client_socket);
    free(arg);
    return NULL;
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_length = sizeof(client_address);

    // Create the server socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Error creating server socket");
        exit(1);
    }

    // Configuring
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002); // Port number
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
        int *client_socket_ptr = malloc(sizeof(int));
        *client_socket_ptr = client_socket;
        pthread_t tid;
        if (pthread_create(&tid, NULL, handle_client, (void *)client_socket_ptr) != 0) {
            perror("Error creating thread");
        }
    }

   
    close(server_socket);

    return 0;
}
