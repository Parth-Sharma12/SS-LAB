/*
============================================================================
Name : 32c.c
Author : Parth Sharma
Description : Write a program to implement semaphore to protect any critical section.
a. rewrite the ticket number creation program using semaphore
b. protect shared memory from concurrent write access
c. protect multiple pseudo resources ( may be two) using counting semaphore
d. remove the created semaphore
Date:6th oct,2023.
============================================================================
*/
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>

int main() {
    sem_t *sem;
    sem = sem_open("/shared_memory_semaphore", O_CREAT, 0644, 1); // Create a binary semaphore

    int* shared_memory;
    int size = sizeof(int);
    
    int fd = shm_open("/my_shared_memory", O_CREAT | O_RDWR, 0644);
    //sets size of shared memory to size of integer
    ftruncate(fd, size);

    //mapping the shared memory segment to current process address space allowing both reading and writing and allowing for sharing  
    shared_memory = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    sem_wait(sem); // Acquire the semaphore to protect critical section

    *shared_memory = 42;

    sem_post(sem); // Release the semaphore

    close(fd);
    sem_close(sem); // Close the semaphore
    sem_unlink("/shared_memory_semaphore"); // Remove the semaphore

    return 0;
}
