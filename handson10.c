#include<sys/types.h>
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
int main(){	
	int fd;
	char buff[10] = "Hey_I_am__";
	int offset = 10;
	fd = open("handson10.txt",O_RDWR);
	if(fd == -1){
		perror("Error:");
	}
	else{
		write(fd,buff,strlen(buff));	
}
	int val = lseek(fd,offset,SEEK_CUR);
	printf("Return value of seek :%d\n",val);
	write(fd,buff,strlen(buff));
}
