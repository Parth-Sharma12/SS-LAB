#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipe_fd[2];
    pid_t child_pid;

    // Creating a pipe
    if (pipe(pipe_fd) == -1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    // Forking a child process
    child_pid = fork();

    if (child_pid < 0) {
        perror("Forking failed");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // Child process
        close(pipe_fd[1]);  // Closing the write end of the pipe

        char buffer[100];
        ssize_t num_bytes;

        //sleep(1);

        num_bytes = read(pipe_fd[0], buffer, sizeof(buffer));
        if (num_bytes < 0) {
            perror("Read from pipe failed");
            exit(EXIT_FAILURE);
        }

        // Null-terminate the received data
        buffer[num_bytes] = '\0';

        printf("Received message from parent: %s\n", buffer);

        close(pipe_fd[0]);  // Closing the read end of the pipe in the child process
    } else {
        // Parent process
        close(pipe_fd[0]);  // Closing the read end of the pipe

        char message[] = "Hello! this is parent!";
        ssize_t num_bytes;


        num_bytes = write(pipe_fd[1], message, strlen(message));

        if (num_bytes < 0) {
            perror("Write to pipe failed");
            exit(EXIT_FAILURE);
        }

        close(pipe_fd[1]);  // Closing the write end of the pipe in the parent process
    }

    return 0;
}
