/*
============================================================================
Name : 32a.c
Author : Parth Sharma
Description : Write a program to implement semaphore to protect any critical section.
a. rewrite the ticket number creation program using semaphore
b. protect shared memory from concurrent write access
c. protect multiple pseudo resources ( may be two) using counting semaphore
d. remove the created semaphore
Date:6th oct,2023.
============================================================================
*/
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
int main()
{
  struct
  {
    int train_num;
    int ticket_no;
  } db[3];
  int fd;
  for(int i=0;i<3;i++)
  {
   db[i].train_num = i+1;
   db[i].ticket_no = i+1;
  }
  fd = open("record_32.txt",O_CREAT|O_RDWR,0644);
  write(fd,&db,sizeof(db));
  close(fd);
}

