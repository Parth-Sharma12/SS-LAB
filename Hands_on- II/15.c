#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
int main(){
	int fd[2];
	pipe(fd);
	char buffer[50];
	if(pipe(fd)==-1){
		printf("ERROR");
	}
	else{
		pid_t child = fork();
		if(child == 0){
			wait(0);
			close(fd[1]);
			read(fd[0],buffer,sizeof(buffer)); //put in buffer
			printf("Parent process sent %s",buffer);
			close(fd[0]);
		}
		else{
			close(fd[0]);
			const char *message = "Hello Child, I am your parent";
			write(fd[1],message,strlen(message));
			close(fd[1]);
		}
	}
}