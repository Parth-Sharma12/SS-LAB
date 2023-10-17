#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<string.h>
#include<sys/stat.h>
#include<unistd.h>
int main(){
	printf("WRITTEN\n");
	const char* fifoname = "/tmp/myfifo";
	printf("WRITTEN\n");
	const char *message = "Hey I am process 1 sending the message\n";
	if(access(fifoname,F_OK)==-1){    //If file doesn't exist create it 
		if(mkfifo(fifoname,0666)==-1){
			perror("Errrror");
			exit(EXIT_FAILURE);
		}
	}
	if(chmod(fifoname,0666)==-1){
		perror("Error");
		exit(EXIT_FAILURE);
	}
	printf("Fifo created: %s\n",fifoname);
	int fd = open(fifoname,O_WRONLY);  //FIFO's are just like another file
	printf("WRITTEN\n");
	write(fd,message,strlen(message));
	
	close(fd); 
	
}