#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
int main(){
	FILE* file = fopen("handson17.txt","r+");
	int ticket = 0;
	int fd = open("handson17.txt",O_RDWR);
	
	
	struct flock write_lock;
	write_lock.l_type = F_WRLCK;
	write_lock.l_whence = SEEK_SET;
	write_lock.l_start = 0;
	write_lock.l_len  =0;
	write_lock.l_pid = getpid();
	printf("Before Critical section:\n");
	fcntl(fd,F_SETLKW,&write_lock);
	lseek(fd,0,SEEK_SET); //To set pointer on the ticket number 
	read(fd,&ticket,sizeof(ticket));//To read from file
	printf("Tickets Remaining:%d\n",ticket);
	ticket++;
	lseek(fd,0,SEEK_SET);
	write(fd,&ticket,sizeof(ticket));
	printf("Ticket_No:%d\n",ticket);
	printf("Enter to unlock:\n");
	getchar();
	write_lock.l_type = F_UNLCK;
	printf("Unlocked\n");
	fcntl(fd,F_SETLK,&write_lock);
	printf("Done\n");

	
}
