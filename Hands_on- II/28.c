#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
    int msqid;
    key_t key;
    struct msqid_ds queueInfo;

   
    key = ftok("/tmp", 'A');

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

    // Retrieve current message queue settings
    if (msgctl(msqid, IPC_STAT, &queueInfo) == -1) {
        perror("msgctl IPC_STAT");
        exit(1);
    }

    // Modify the permissions 
    queueInfo.msg_perm.mode = 0777;
    
    // Update the message queue with the new permissions
    if (msgctl(msqid, IPC_SET, &queueInfo) == -1) {
        perror("msgctl IPC_SET");
        exit(1);
    }

    printf("Message queue permissions updated successfully.\n");

    return 0;
}
