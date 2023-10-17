#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <time.h>

int main() {
    int msqid;
    key_t key;
    struct msqid_ds msq_info;

    // Give any key value
    key = ftok("/tmp", 'A');

    // Open the message queue
    if ((msqid = msgget(key, 0666 | IPC_CREAT)) == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    if (msgctl(msqid, IPC_STAT, &msq_info) == -1) {   //msq_info is the pointer to the structure where information is stored
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

    printf("Message Queue Info:\n");
    printf("a. Access Permissions: %#o\n", msq_info.msg_perm.mode);
    printf("b. UID: %d, GID: %d\n", msq_info.msg_perm.uid, msq_info.msg_perm.gid);
    printf("c. Time of Last Message Sent: %s", ctime(&msq_info.msg_stime));
    printf("   Time of Last Message Received: %s", ctime(&msq_info.msg_rtime));
    printf("d. Time of Last Change: %s", ctime(&msq_info.msg_ctime));
    printf("e. Size of the Queue: %ld bytes\n", msq_info.msg_qbytes);
    printf("f. Number of Messages in the Queue: %ld\n", msq_info.msg_qnum);
    printf("g. Maximum Number of Bytes Allowed: %ld\n", msq_info.msg_qbytes);
    printf("h. PID of msgsnd: %d, PID of msgrcv: %d\n", msq_info.msg_lspid, msq_info.msg_lrpid);

    // Close the message queue (optional)
    msgctl(msqid, IPC_RMID, NULL);

    return 0;
}
