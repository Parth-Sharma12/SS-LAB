#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int pipe_fd[2];
    pid_t pid;

    if (pipe(pipe_fd) == -1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid == -1) {
        perror("Forking failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process

        // Close read end
        close(pipe_fd[0]);
        
        dup2(pipe_fd[1], STDOUT_FILENO);// Redirect standard output to the write end of the pipe

        
        close(pipe_fd[1]);// Closing the original write end

        execlp("ls", "ls", "-l", NULL); //Executing -l
    } else {
        // Parent process

        // Close the write end
        close(pipe_fd[1]);
        dup2(pipe_fd[0], STDIN_FILENO);  // Redirecting standard input to the read end

        // Close the original read end of the pipe
        close(pipe_fd[0]);
    
        execlp("wc", "wc", NULL); //Execute wc
    }

    return 0;
}
