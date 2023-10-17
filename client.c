#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include<sys/wait.h>
#include<arpa/inet.h>
//#include "Structures.c"
#include "ADMIN.c"
int main() {
    int client_socket;
    struct sockaddr_in server_addr;

    // Create a socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed");
        exit(1);
    }
    // Configure the server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080); // Use the same port as the server
    server_addr.sin_addr.s_addr = inet_addr("192.168.1.8"); // Use the server's IP address (localhost)

    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        exit(1);
    }

    printf("Connected to the server.\n");
    // Printing MENU
    char buff[1000];
    recv(client_socket,buff,sizeof(buff),0);
    printf("Menu %s",buff);

    //Selecting Login as
    char choice_buffer[2];
    fgets(choice_buffer, sizeof(choice_buffer), stdin);
    send(client_socket, choice_buffer, sizeof(choice_buffer), 0);
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    //Displaying options
    char buff1[1000];
    read(client_socket,buff1,sizeof(buff1));
    printf("%s\n",buff1);

    int choice;
    fflush(stdout);
    printf("\nEnter your choice:\n");
    scanf("%d",&choice);
    write(client_socket, &choice, sizeof(choice));
    Admin(choice,client_socket);
    // Close the socket when done
    close(client_socket);
}
