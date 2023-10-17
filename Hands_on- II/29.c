#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
    int msqid;
    key_t key;

    // Generate a key for the message queue (use the same key as the sender)
    key = ftok("/tmp", 'A'); // You can choose any file path and character

    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Open the message queue
    msqid = msgget(key, 0666);

    if (msqid == -1) {
        perror("msgget");
        exit(1);
    }

    // Remove the message queue
    if (msgctl(msqid, IPC_RMID, NULL) == -1) { //msgctl system call allows you to control message queues
        perror("msgctl IPC_RMID");
        exit(1);
    }

    printf("Message queue removed successfully.\n");

    return 0;
}
