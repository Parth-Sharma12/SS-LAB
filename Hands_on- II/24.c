#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
    key_t key;
    int msgid;

    // Generate a unique key for the message queue
    key = ftok("/tmp", 'B'); // A == 0, B == 1...

    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    //Message queue
    msgid = msgget(key, 0666 | IPC_CREAT);   //Queue Id is created by OS so that processes can access the queue using that
                                             // Key is given by user to access the queue , It is a way to name queue                          
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    printf("Message Queue Key: %d\n", key);
    printf("Message Queue ID: %d\n", msgid);

    return 0;
}
