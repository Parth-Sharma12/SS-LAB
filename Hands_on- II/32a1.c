/*
============================================================================
Name : 32b.c
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
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <fcntl.h>
int main()
{
  int input;
  printf("ENTER THE TRAIN NUMBER : ");
  scanf("%d",&input);
  int fd = open("record_32.txt",O_RDWR);
  struct
  {
    int train_number;
    int ticket_count;
  } db;
  // Create or get the semaphore 
  sem_t* semaphore = sem_open("/my_semaphore", O_CREAT, 0644, 1); 
  printf("BEFORE ENTERING INTO CRITICAL SECTION :\n");
  sleep(1);
  sem_wait(semaphore);
  lseek(fd,(input-1)*sizeof(db),SEEK_SET);
  read(fd,&db,sizeof(db));
  printf("CURRENT TICKET COUNT :%d\n",db.ticket_count);
  db.ticket_count++;
  lseek(fd,-1*sizeof(db),SEEK_CUR);
  write(fd,&db,sizeof(db));
  sleep(1);
  printf("UPDATED TICEKT COUNT :%d\n",db.ticket_count);
  sleep(1);
  printf("TO BOOK PRESS ENTER\n");
  getchar();
  getchar();
  printf("BOOKED\n");
  sem_post(semaphore);
  sem_close(semaphore);
  close(fd);
}
