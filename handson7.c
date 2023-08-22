#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
int main(int argc,char* argv[])
{
if(argc!=3)
{
    printf("please read about cp first");
    return -1;
}
int fd_read=open(argv[1],O_RDONLY);
int fd_write=open(argv[2],O_WRONLY|O_CREAT);
if(fd_read || fd_write == -1)
    printf("Useless");
while(1)
{
char buff;
int char_read=read(fd_read,&buff,1);
if(char_read==-1)
    break;
int char_written=write(fd_write,&buff,1);
}
int fd_read_close=close(fd_read);
int fd_write_close=close(fd_write);
if(fd_read_close || fd_write_close == -1)
   printf("Useless:could not close");
return 0;
}
