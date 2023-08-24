#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    fd_set fds;
    struct timeval timeout;
    int val;

    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);

    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    printf("Waiting for input..\n");

    val = select(STDIN_FILENO + 1, &fds, NULL, NULL, &timeout);//(File_descriptor,FD_SET for read,for write,for error,tells how much time select should wait for an i/o event

    if (val == -1) {  //Means error occured");
        perror("select");
        return 1;
    } else if (val == 0) { //Means no descriptor is ready
        printf("No input received within 10 seconds.\n");
    } else {
        if (FD_ISSET(STDIN_FILENO, &fds)) {  //descriptor with STDIN_FILENO is ready
            printf("Input received within 10 seconds.\n");
        }
    }

    return 0;
}
