#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>

int main() {
    // Get the maximum number of files a process can open
    struct rlimit rlim; // getrlimit helps finding the number of resources a process can have
    if (getrlimit(RLIMIT_NOFILE, &rlim) == 0) { //RLIMIT_NOFILE specifies no. of files a process can open
        printf("Maximum number of files a process can open:%llu\n", (unsigned long long)rlim.rlim_cur);
    } else {
        perror("getrlimit");
        return 1;
    }

    // Create a pipe to determine the size of the pipe (circular buffer)
    int pipe_fd[2];  //2 fd's read end and write end
    if (pipe(pipe_fd) == 0) {
        long pipe_size = fpathconf(pipe_fd[0], _PC_PIPE_BUF); //used to query the configurable system limits or options associated with a specific file or file descriptor.   
        if (pipe_size != -1) { //pipe_fd[0] is the file descriptor of the read end of the pipe, and _PC_PIPE_BUF is the constant indicating that we want to query the size of the pipe buffer.
            printf("Size of a pipe (circular buffer): %ld bytes\n", pipe_size);
        } else {
            perror("fpathconf");
            return 1;
        }
    } else {
        perror("pipe");
        return 1;
    }

    return 0;
}
