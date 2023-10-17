/*
============================================================================
Name : 32d.c
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
#include <semaphore.h>

int main() {
    sem_t sem;
    sem_init(&sem, 0, 2); // Initialize a counting semaphore with initial value 2

    sem_wait(&sem); // Acquire a resource
    printf("Resource 1 acquired\n");
    // Critical Section for Resource 1
    sem_post(&sem); // Release a resource

    sem_wait(&sem); // Acquire another resource
    printf("Resource 2 acquired\n");
    // Critical Section for Resource 2
    sem_post(&sem); // Release another resource

    sem_destroy(&sem); // Destroy the semaphore

    return 0;
}

