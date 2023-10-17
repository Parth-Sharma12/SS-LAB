#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
	char buffer[50];
	const char* fifoname = "/tmp/myfifo";
	int fd = open(fifoname,O_RDONLY);
	read(fd,buffer,sizeof(buffer));
	printf("Message sent by program 1:%s",buffer);
	close(fd);
}