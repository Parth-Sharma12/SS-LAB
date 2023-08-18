#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

void main(void){
	int fd1,fd2;
	fd1 = open("file1.txt",O_RDWR,O_EXCL);
	fd2 = open("file1.txt",O_RDWR);
	printf("First file: %d \n",fd1);
	printf("Second file: %d",fd2);
}
