#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
int main(){
	//USING MKNOD
	int fd1 = mknod("fifo_file1",S_IFIFO,0);   //mknod is a general-purpose command for creating various types of special files
	if(fd1==-1){
		printf("ERROR in fd1\n");
	}
	int fd2 = mkfifo("fifo_file2",0666);//read and write permissions //mkfifo is specifically designed for creating named pipes
	if(fd2 == -1){
		printf("ERROR in fd2\n");
	}
}
//Will create a file in the directory when the command will be ran