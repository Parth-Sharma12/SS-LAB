#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main()
{
 int fd=open("Test.txt",O_RDWR|O_APPEND);
 if(fd<0)
 {
  perror("ERROR : ");
 }
 //USING DUP SYSTEM CALL
 //ASSIGNS LOWEST NUMBERED UNUSED FILE DESCRIPTOR TO COPIED_FD 
 int copied_fd = dup(fd);
 //BOTH FILE DESCRIPTORS MODIFIES THE SAME FILE TEST.TXT
 write(fd,"writing using original file descriptor\n",39);
 write(copied_fd,"writing using copied file descriptor\n",37);

 // USING DUP2 SYSTEM CALL 
 if(fd>0)
 {
  close(fd);
 }
 fd= open("Test2.txt",O_RDWR|O_APPEND);
 if(fd<0)
 {
  perror("ERROR :");
 }
  int copied_dup2 = dup2(fd,5);
  write(fd,"writing using original file descriptor :\n",39);
  write(copied_dup2,"writing using copied file descriptor :\n",37);
 //USING FCNTL FUNCTION
 if(fd>0)
 {
  close(fd);
 }
 fd=open("Test3.txt",O_RDWR|O_APPEND);
 int copied_fcntl = fcntl(fd, F_DUPFD,10);
 if(copied_fcntl<0)
 {
  perror("ERROR :");
 }
 write(fd,"writing using original file descriptor :\n",39);
 write(copied_fcntl,"writing using copied file descriptor :\n",37); 
}
