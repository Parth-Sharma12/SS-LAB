#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {

    // Open the FIFO for writing
    int fifoFd = open("myfifo_22", O_WRONLY);

    if (fifoFd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Data to be written into the FIFO
    const char *message = "Hello, FIFO!";

    // Write the data into the FIFO
    ssize_t bytesWritten = write(fifoFd, message, strlen(message));

    if (bytesWritten == -1) {
        perror("write");
    } else {
        printf("Data written to FIFO: %s\n", message);
    }

    // Close the FIFO
    close(fifoFd);

    return 0;
}
