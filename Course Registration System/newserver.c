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
int id=0;
#define PORT 3243
int Faculty_id = 0;
int main(){

	int sockfd, ret;
	 struct sockaddr_in serverAddr;

	int client_socket;
	struct sockaddr_in newAddr;

	socklen_t addr_size;

	char buffer[1024];
	pid_t childpid;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Server Socket is created.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("[-]Error in binding.\n");
		exit(1);
	}
	printf("[+]Bind to port %d\n", 4444);

	if(listen(sockfd, 10) == 0){
		printf("[+]Listening....\n");
	}else{
		printf("[-]Error in binding.\n");
	}


	while(1){
		client_socket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);
		if(client_socket < 0){
			exit(1);
		}
		printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));

		if((childpid = fork()) == 0){
			close(sockfd);

			while(1){
				send(client_socket,"************************* Welcome to academia ************************\n Choose an option to continue\n 1)Admin \n 2)Professor \n 3)Student\n ",1000,0);
    			char choice_buffer[2];
    			recv(client_socket, choice_buffer, sizeof(choice_buffer), 0);
    			int option = atoi(choice_buffer);
    			choice_buffer[0]='\0';
    			
    			if(option==1){ //ADMIN
    				int admin_exit = 0;
    				while(admin_exit == 0){
	    				int answer;
	        			printf("Sending\n");
	        			const char *options = "Choose from the following options\n 1) Add Student \n 2) View Student Details \n 3) Add Faculty\n 4) View Faculty Details\n 5) Activate Student\n 6) Block Student\n 7) Modify Student Details\n 8) Modify Faculty Details\n 9) Logout and Exit\n ";
	    				write(client_socket,options,strlen(options));
	        			read(client_socket,&answer,sizeof(int));
	        			performAdmin_Task(answer,client_socket,id,&admin_exit);	
	        		}
    			}
    			int br = 0;
    			if(option==2){ //Professor
    				int faculty_exit = 0;
    				
					int answer;
        			printf("Sending\n");
        			char login[30];
        			char password[30];
        			send(client_socket,"Enter login id:",20,0);
        			recv(client_socket,login,sizeof(login),0);
        			send(client_socket,"Enter Password:",20,0);
        			recv(client_socket,password,sizeof(password),0);
        			printf("%s\n",password);
        			printf("%s\n",login);

        			
	            	int br1 = searchFacultyByID(login,client_socket,password,br);
	            	if(br1 == 1){ // Password is incorrect come out of the loop
	            		continue;
	            	}
		       		while(faculty_exit == 0){
	        			const char *options = "Choose from the following options\n 1) Add New Course \n 2) View Offering Courses \n 3) Update Course Details \n 4) Remove Course from Catalog \n 5) Change Password \n 6) Logout And Exit \n";
	    				write(client_socket,options,strlen(options));
	        			read(client_socket,&answer,sizeof(int));
	        			performFaculty_Task(answer,client_socket,login,&faculty_exit);
	    			}	
    			}
    			if(option==3){ //Student
    				int student_exit = 0;
    				int answer1;
        			printf("Sending\n");
        			char login[30];
        			char password[30];
        			send(client_socket,"Enter login id:",20,0);
        			recv(client_socket,login,sizeof(login),0);
        			send(client_socket,"Enter Password:",20,0);
        			recv(client_socket,password,sizeof(password),0);
        			printf("%s\n",password);
        			printf("%s\n",login);

        			
	            	int br1 = searchStudentByID(login,client_socket,password,br);
	            	if(br1 == 1){ // Password is incorrect come out of the loop
	            		continue;
	            	}
	            	while(student_exit == 0){
	            		const char *options1 = "Choose from the following options\n 1) View Courses \n 2) Enroll (Pick) New Course\n 3) View Enrolled Course Details\n 4) Drop Course \n 5) Change Password \n 6) Logout And Exit \n";
	    				write(client_socket,options1,strlen(options1));
	        			read(client_socket,&answer1,sizeof(int));
	        			performStudent_Task(answer1,client_socket,login,&student_exit);
	            	}		
    			}	
			}
		}

	}

	close(client_socket);
	return 0;
}