#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

//message structure
struct msgbuf {
    long mtype;     // Message type (must be greater than 0)
    char mtext[100]; // Message text
};

int main() {
    int msqid;
    key_t key;
    struct msgbuf message;

   
    key = ftok("/tmp", 'A'); 

    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    msqid = msgget(key, 0666);

    if (msqid == -1) {
        perror("msgget");
        exit(1);
    }

    // Receive and display messages from the queue with blocking (0) flag
    //just run 26.c to send the message or to fill the queue.. after receiving a message it will be deleted from the queue
        while (1) {
            if (msgrcv(msqid, &message, sizeof(message.mtext), 1, 0) == -1) { // Will wait until the message is not available in the queue
                perror("msgrcv");
                exit(1);
            }

            printf("Received Message (Blocking): %s\n", message.mtext);
            break;
        }


     // Receive and display messages from the queue with IPC_NOWAIT flag (non-blocking)
    while (1) {
        if (msgrcv(msqid, &message, sizeof(message.mtext), 1, IPC_NOWAIT) == -1) {
            perror("msgrcv");
            // If no message is available, this will print an error and it will keep running 
        } else {
            printf("Received Message (Non-blocking): %s\n", message.mtext);
        }

    return 0;
}
}
