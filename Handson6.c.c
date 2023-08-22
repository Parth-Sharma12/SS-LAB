#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main()
{

int write_count=0;
write_count=write(1,"HELLO_WORLD_TWILIGHT\n",22);
if(write_count==-1)
{
  printf("FAILURE");
}
else
{
  printf("TOTAL NUMBER OF BYTES WRITTEN : %d\n",write_count);
}
int read_count=0;
char buff[100];
read_count=read(0,buff,21);
if(read_count == -1)
{
  printf("FAILURE");
}
else
{
  write(1,buff,21);
  printf("TOTAL NUMBER OF BYTES READ ON SCREEN  : %d\n",read_count);
}

}
