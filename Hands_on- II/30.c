#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024 

int main() {
    key_t key = ftok("/tmp", 'A');  // unique key for the shared memory

    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Creates the shared memory if doesn't exist or get the shared memory segment using given key
    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);

    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // creates a pointer to the shared memory with read-write permissions
    char *shmaddr = shmat(shmid, NULL, SHM_R);

    strncpy(shmaddr, "Hello, Shared Memory!", SHM_SIZE); //Data to shared memory

    // Detaching the shared memory
    if (shmdt(shmaddr) == -1) {
        perror("shmdt");
    }

    // Attach the shared memory with read-only permissions
    shmaddr = shmat(shmid, NULL, SHM_RDONLY);


    // Attempting to overwrite the shared memory
    strncpy(shmaddr, "This will not work", SHM_SIZE);

    // Detaching the shared memory
    if (shmdt(shmaddr) == -1) {
        perror("shmdt");
    }

    // Removing the shared memory segment
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl (IPC_RMID)");
    } else {
        printf("Shared memory removed.\n");
    }

    return 0;
}
