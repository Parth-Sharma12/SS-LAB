#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

int main() {
    sem_t binarySemaphore, countingSemaphore;

    //Binary semaphore
    if (sem_init(&binarySemaphore, 0, 1) == -1) {
        perror("");
        exit(1);
    }

    // counting semaphore with range 0-5
    if (sem_init(&countingSemaphore, 0, 5) == -1) {
        perror("");
        exit(1);
    }

    // initial values of both semaphores
    int binaryValue, countingValue;
    sem_getvalue(&binarySemaphore, &binaryValue);
    sem_getvalue(&countingSemaphore, &countingValue);

    printf("Binary Semaphore Initial Value: %d\n", binaryValue);
    printf("Counting Semaphore Initial Value: %d\n", countingValue);

    sem_destroy(&binarySemaphore);
    sem_destroy(&countingSemaphore);

    return 0;
}
