/*
============================================================================
Name : 21a.c
Author : Parth Sharma

Description : Write two programs so that both can communicate by FIFO -Use two way communications.
Date:25th Sep,2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
int main() 
{
    int fd;
    fd = open("fifo1", O_RDWR|O_CREAT, 0777);
    char message[] = "Hello from Writer!\n";
    write(fd, message, sizeof(message));
    char response[100];
    int bytesRead = read(fd, response, sizeof(response));
    if (bytesRead > 0) 
    {
        response[bytesRead] = '\0';  // Null-terminate the string
        printf("Received response: %s\n", response);
    }
    close(fd);
    return 0;
}


