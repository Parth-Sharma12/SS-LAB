#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "ADMIN.c"
#include "Faculty.c"
#include "Student.c"
#define PORT 3243

int main(){

	int client_socket, ret;
	struct sockaddr_in serverAddr;
	char buffer[1024];

	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if(client_socket < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Client Socket is created.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = connect(client_socket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Connected to Server.\n");

	while(1){
		char buff[1000];
    	recv(client_socket,buff,sizeof(buff),0);
    	printf("%s\n",buff);
    	buff[0] = '\0';
    	//memset(buff, 0, sizeof(buff));
    	
    	//Selecting Login as
    	char choice_buffer[2];
    	scanf("%s",choice_buffer);
    	send(client_socket, choice_buffer, sizeof(choice_buffer), 0);
    	//choice_buffer[0]='\0';
  		int option = atoi(choice_buffer); 

    	if(option==1){
    		int admin_exit1 = 0;
    		while(admin_exit1 == 0){
    			char buff4[1000];
		    	read(client_socket,buff4,sizeof(buff4));
		    	printf("%s\n",buff4);
		    	buff4[0]='\0';

		    	int choice;
		    	fflush(stdout);
		    	printf("\nEnter your choice:\n");
		    	scanf("%d",&choice);
		    	write(client_socket, &choice, sizeof(choice));
	    		Admin(choice,client_socket,&admin_exit1);
    		}
    		
    	}
		else if(option==2){
			int faculty_exit1 = 0;
			
			char loginbuff[50];
			char login[30];
			char passbuff[50];
			char pass[30];
			recv(client_socket,loginbuff,sizeof(loginbuff),0);
			printf("%s\n",loginbuff);
			scanf("%s",login);
			send(client_socket,login,sizeof(login),0);

			recv(client_socket,passbuff,sizeof(passbuff),0);
			printf("%s\n",passbuff);
			scanf("%s",pass);
			send(client_socket,pass,sizeof(pass),0);

			int verification[2];
		
			recv(client_socket,verification,sizeof(verification),0);
			send(client_socket,"Ok",5,0);
			if(verification[0]==1){
				printf("Sorry Username/password is incorrect\n");
				break;
			}
			else{
				printf("Login successful\n");
			}
			while(faculty_exit1==0){	
				char buff1[1000];
		    	read(client_socket,buff1,sizeof(buff1));
		    	printf("%s\n",buff1);
		    	buff1[0]='\0';

		    	int choice;
		    	//fflush(stdout);
		    	printf("Enter your choice:\n");
		    	scanf("%d",&choice);
		    	write(client_socket, &choice, sizeof(choice));
				Faculty(choice,client_socket,login,&faculty_exit1);
				}
		}   		
		else if(option==3){
			int student_exit1 = 0;
			char loginbuff1[50];
			char login1[30];
			char passbuff1[50];
			char pass1[30];
			recv(client_socket,loginbuff1,sizeof(loginbuff1),0);
			printf("%s\n",loginbuff1);
			scanf("%s",login1);
			send(client_socket,login1,sizeof(login1),0);

			recv(client_socket,passbuff1,sizeof(passbuff1),0);
			printf("%s\n",passbuff1);
			scanf("%s",pass1);
			send(client_socket,pass1,sizeof(pass1),0);

			int verification1[2];

			recv(client_socket,verification1,sizeof(verification1),0);
			send(client_socket,"Ok",5,0);
			if(verification1[0]==1){
				printf("Sorry username/password is incorrect\n");
				break;
			}
			else{
				printf("Login successful\n");
			}
			while(student_exit1 == 0){
				char buff2[1000];
		    	read(client_socket,buff2,sizeof(buff2));
		    	printf("%s\n",buff2);
		    	buff2[0]='\0';

		    	int choice1;
		    	fflush(stdout);
		    	printf("\nEnter your choice:\n");
		    	scanf("%d",&choice1);
		    	write(client_socket, &choice1, sizeof(choice1));
				Student(choice1,client_socket,login1,&student_exit1);
			}	
		}   		
		}
	//choice_buffer[0]='\0';	
	close(client_socket);
}
