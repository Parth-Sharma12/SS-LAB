#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
int main(){
	int fd1[2];
	int fd2[2];
	char buffer1[50];
	char buffer2[50];
	pipe(fd1);
	pipe(fd2);
	if(pipe(fd1)==-1 || pipe(fd2)==-1){
		printf("ERROR");
		exit(0);
	}
	else{
		pid_t child = fork();
		if(child == 0){
			close(fd1[1]); //Parent will write in fd1[1]
			const char* message = "Hello I am your child\n";
			write(fd2[1],message,strlen(message));
			read(fd1[0],buffer1,sizeof(buffer1));
			printf("Parent says: %s",buffer1);
			close(fd1[1]);
			close(fd2[0]);
			close(fd1[0]);
			close(fd2[1]);
		}
		else{
			close(fd2[1]);//Child process writes here
			const char* message = "Hello I am your parent\n";
			write(fd1[1],message,strlen(message));
			read(fd2[0],buffer2,sizeof(buffer2));
			printf("Child Says:%s",buffer2);
			close(fd1[1]);
			close(fd2[0]);
			close(fd1[0]);
			close(fd2[1]);
		}
	}
}