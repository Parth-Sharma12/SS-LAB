#include<stdlib.h>
#include<unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "Structures.c"

#include <fcntl.h>
int extractNumericId1(const char *id) {
        int numericId;
        sscanf(id, "MT@%d", &numericId);
        return numericId;
}
void generateNewId1(char *newId, int highestId) {
        sprintf(newId, "MT@%d", highestId + 1);
}

void performAdmin_Task(int choice, int client_socket,int id,int *admin_exit) {
    switch (choice) {
        case 1: //Add user
            int file3 = open("student_data.txt", O_RDWR);
            
            struct student student;
            send(client_socket, "Enter password:", 40, 0);
            recv(client_socket, student.password, sizeof(student.password), 0);

            send(client_socket, "Enter name:", 40, 0);
            recv(client_socket, student.name, sizeof(student.name), 0);
        
            send(client_socket, "Enter email: ", 14, 0);
            recv(client_socket, student.email, sizeof(student.email), 0);

            send(client_socket, "Enter address: ", 16, 0);
            recv(client_socket, student.address, sizeof(student.address), 0);

            int new_id = 0;
            struct student stucpy;
            struct stat file_info;
            fstat(file3, &file_info);
            char New[20];
           
            if(file_info.st_size != 0){
                lseek(file3,-(sizeof(struct student)),SEEK_END);
                read(file3,&stucpy,sizeof(struct student));
                generateNewId1(New,extractNumericId1(stucpy.id));
            }
            else{
                strcpy(New,"MT@1");
            }
            
            strcpy(student.id,New);
            student.actv = 1;
            lseek(file3,0,SEEK_END);
            write(file3,&student,sizeof(struct student));
            close(file3);            
            break;
        case 2:
            char ID[20];
            int found = 0;
            send(client_socket,"Enter Id to search: ",30,0);
            recv(client_socket,ID,sizeof(ID),0);
            void searchStudentByID(char *ID) {
                struct student student;
                int fd1 = open("student_data.txt", O_RDONLY);

                int numid = extractNumericId1(ID);
                int offset = (numid-1)*sizeof(struct student);
                lseek(fd1,offset,SEEK_SET);
                read(fd1,&student,sizeof(struct student));
                if(strcmp(student.id,ID)==0){
                    char re1[5];
                    send(client_socket,&student,sizeof(struct student),0);
                    recv(client_socket,re1,sizeof(re1),0);
                    found = 1;
                }
            if (!found) {
                printf("Student with ID '%s' not found.\n", ID);
            }
                close(fd1);
            }
            searchStudentByID(ID);
            break;
        case 3:
            struct Faculty faculty;
            int file1 = open("faculty.txt", O_RDWR);
            send(client_socket,"Send_data of faculty (PLEASE USE UNDERSCORE INSTEAD OF WHITESPACE)\n",100,0);
            recv(client_socket, &faculty, sizeof(faculty), 0);
            printf("Data received\n");

            //Generating an ID for Faculty

            int extractNumericId(const char *id) {
                int numericId;
                sscanf(id, "iiitb@%d", &numericId);
                return numericId;
            }
            void generateNewId(char *newId, int highestId) {
                sprintf(newId, "iiitb@%d", highestId + 1);
            }
            struct Faculty facultycpy;
            
            char New1[20];
            if(SEEK_END>0){
                lseek(file1,-(sizeof(struct Faculty)),SEEK_END);
                read(file1,&facultycpy,sizeof(struct Faculty));
                generateNewId(New1,extractNumericId(facultycpy.id));
            }
            
            strcpy(faculty.id,New1);
            lseek(file1,0,SEEK_END);
            write(file1,&faculty,sizeof(struct Faculty));
            close(file1);
           
            break;
        case 4:
            char ID1[20];
            send(client_socket,"Enter Id to search: ",30,0);
            recv(client_socket,ID1,sizeof(ID1),0);
            void searchFacultyByID(char *ID) {
                struct Faculty faculty;
                int file = open("faculty.txt", O_RDONLY);

                int numid1 = extractNumericId(ID);
                int offset1 = (numid1-1)*sizeof(struct Faculty);
                lseek(file,offset1,SEEK_SET);
                read(file,&faculty,sizeof(struct Faculty));
                if (strcmp(faculty.id,ID)==0) {
                    char re[5];
                    send(client_socket,&faculty,sizeof(struct Faculty),0);
                    recv(client_socket,re,sizeof(re),0);
                
                    found = 1;
                }
                if (!found) {
                printf("Faculty with ID '%s' not found.\n", ID);
            }      
                close(file);
            }
            searchFacultyByID(ID1);
            break;
        case 5:
            char id_ac[50];
            send(client_socket,"Enter student Id to activate:",30,0);
            recv(client_socket,id_ac,sizeof(id_ac),0);
            int ac_file = open("student_data.txt",O_RDWR);
            int act = extractNumericId1(id_ac);
            int off_ = (act-1)*sizeof(struct student);
            lseek(ac_file,off_,SEEK_SET);
            struct student stucpy1;
            struct student stucpy2;
            read(ac_file,&stucpy1,sizeof(struct student));
            strcpy(stucpy2.id,stucpy1.id);
            strcpy(stucpy2.name,stucpy1.name);
            strcpy(stucpy2.password,stucpy1.password);
            strcpy(stucpy2.email,stucpy1.email);
            strcpy(stucpy2.address,stucpy1.address);
            stucpy2.actv = 1;
            lseek(ac_file,-(sizeof(struct student)),SEEK_CUR);
            write(ac_file,&stucpy2,sizeof(struct student));
            send(client_socket,"Student Successfully activated.\n",strlen("Student Successfully activated.\n"),0);
            char ack1_[5];
            recv(client_socket,ack1_,sizeof(ack1_),0);
            break;
        case 6:
            char id_ac1_[50];
            send(client_socket,"Enter student Id to block:",30,0);
            recv(client_socket,id_ac1_,sizeof(id_ac1_),0);
            int ac_file_ = open("student_data.txt",O_RDWR);
            int act_ = extractNumericId1(id_ac1_);
            int off__ = (act_-1)*sizeof(struct student);
            lseek(ac_file_,off__,SEEK_SET);
            struct student stucpy1_;
            struct student stucpy2_;
            read(ac_file_,&stucpy1_,sizeof(struct student));
            strcpy(stucpy2_.id,stucpy1_.id);
            strcpy(stucpy2_.name,stucpy1_.name);
            strcpy(stucpy2_.password,stucpy1_.password);
            strcpy(stucpy2_.email,stucpy1_.email);
            strcpy(stucpy2_.address,stucpy1_.address);
            stucpy2_.actv = 0;
            lseek(ac_file_,-(sizeof(struct student)),SEEK_CUR);
            write(ac_file_,&stucpy2_,sizeof(struct student));
            send(client_socket,"Student Successfully Blocked.\n",strlen("Student Successfully Blocked.\n"),0);
            char ack1__[5];
            recv(client_socket,ack1__,sizeof(ack1__),0);
            break;
        case 7:
            int upd = open("student_data.txt",O_RDWR);
            char a1[50];
            send(client_socket,"Enter student id to update",30,0);
            recv(client_socket,a1,sizeof(a1),0);
            char targetcourseID[100];
            strcpy(targetcourseID,a1);
            struct student student_update;

            int numID = extractNumericId1(targetcourseID);
            int offset_ = (numID-1)*sizeof(struct student);
            lseek(upd,offset_,SEEK_SET);
            read(upd,&student_update,sizeof(struct student));
            struct student updatecpy;
            send(client_socket,"Choose from the following which information you want to update\n 1) Name\n 2)Email \n 3) Address\n",1000,0);
            int choice2[2];
            recv(client_socket,choice2,sizeof(choice2),0);
            lseek(upd,-(sizeof(struct student)),SEEK_CUR);
            if(choice2[0] == 1 ){
                char k[50];
                send(client_socket,"Enter the updated name",100,0);
                recv(client_socket,k,sizeof(k),0);
                strcpy(updatecpy.id,student_update.id);
                strcpy(updatecpy.email,student_update.email);
                strcpy(updatecpy.password,student_update.password);
                updatecpy.actv = student_update.actv;
                strcpy(updatecpy.address,student_update.address);
                strcpy(updatecpy.name,k);
                write(upd,&updatecpy,sizeof(struct student));
            }
            else if(choice2[0] == 2 ){
                char new_email[50];
                send(client_socket,"Enter updated email",100,0);
                recv(client_socket,new_email,sizeof(new_email),0);
                strcpy(updatecpy.id,student_update.id);
                strcpy(updatecpy.name,student_update.name);
                strcpy(updatecpy.password,student_update.password);
                updatecpy.actv = student_update.actv;
                strcpy(updatecpy.address,student_update.address);
                strcpy(updatecpy.email,new_email);
                write(upd,&updatecpy,sizeof(struct student));
            }
            else if(choice2[0] == 3){
                char new_Address[50];
                send(client_socket,"Enter updated Address",100,0);
                recv(client_socket,new_Address,sizeof(new_Address),0);
                strcpy(updatecpy.id,student_update.id);
                strcpy(updatecpy.name,student_update.name);
                strcpy(updatecpy.password,student_update.password);
                strcpy(updatecpy.address,new_Address);
                updatecpy.actv = student_update.actv;
                strcpy(updatecpy.email,student_update.email);
                write(upd,&updatecpy,sizeof(struct student));
            }
            close(upd);
            char repl1_[20];
            send(client_socket,"Done",5,0);
            recv(client_socket,repl1_,sizeof(repl1_),0);
            break;
        case 9:
            *admin_exit = 1;
            break;
        default:
            // Invalid choice
            send(client_socket, "Invalid choice.\n", 16, 0);
            break;
    }
    return;
}

//CLIENT SIDE 
void Admin(int choice,int client_socket,int *admin_exit1){
        struct student student;
        switch (choice) {
        case 1:
            char pass[50];
            recv(client_socket,pass,sizeof(pass),0);
            printf(" %s\n",pass);
            scanf("%s",student.password);
            student.password[strcspn(student.password, "\n")] = '\0'; // Remove the newline character
            send(client_socket,student.password, 13, 0);

            char name[100]; 
            recv(client_socket,name,sizeof(name),0);
            printf(" %s\n",name);
            scanf("%s",student.name);
            student.name[strcspn(student.name, "\n")] = '\0'; // Remove the newline character
            send(client_socket,student.name, 13, 0);

            char email[100];
            recv(client_socket,email,sizeof(email),0);
            printf(" %s\n",email);
            scanf("%s",student.email);
            student.email[strcspn(student.email, "\n")] = '\0';
            send(client_socket,student.email,sizeof(student.email), 0);

            char address[100];
            recv(client_socket,address,sizeof(address),0);
            printf(" %s\n",address);
            scanf("%s",student.address);
            student.address[strcspn(student.address, "\n")] = '\0';     
            send(client_socket, student.address, sizeof(student.address), 0);
            break;
        case 2:
            char buff[200];
            char key[20];
            recv(client_socket,buff,sizeof(buff),0);
            printf("%s",buff);
            buff[0] = '\0';

            scanf("%s",key);
            send(client_socket,key,sizeof(key),0);
            key[0]='\0';
            struct student stuinfo;
            recv(client_socket,&stuinfo,sizeof(struct student),0);
            send(client_socket,"ok",2,0);
            printf("ID:%s\n",stuinfo.id);
            printf("name:%s\n",stuinfo.name);
            printf("password:%s\n",stuinfo.password);
            printf("Email:%s\n",stuinfo.email);
            printf("Address:%s\n",stuinfo.address);
            printf("Activate:%d\n",stuinfo.actv);
            
            break;
        case 3:
            char mem[100];
            recv(client_socket,mem,sizeof(mem),0);
            printf("%s\n",mem);
            mem[0] = '\0';
            struct Faculty faculty;
            strcpy(faculty.id,"0");
            char input[50];
            input[0] = '\0';
            fflush(stdin);
            fflush(stdout);

            printf("Enter Password for faculty\n:");
            //memset(input, 0, sizeof(input));
            scanf("%s",input);
            input[strcspn(input, "\n")] = '\0';
            strcpy(faculty.password, input);

            char input_1[50];
            printf("Enter name of the faculty\n:");
            //fgets(input,sizeof(input),stdin);
            //fflush(stdin);
            memset(input_1, 0, sizeof(input_1));
            scanf("%s",input_1);
            input_1[strcspn(input_1, "\n")] = '\0';
            strcpy(faculty.name, input_1);

            char input_2[50];
            printf("Enter Department of the faculty\n:");
            memset(input_2, 0, sizeof(input_2));
            scanf("%s",input_2);
            input_2[strcspn(input_2, "\n")] = '\0';
            strcpy(faculty.department, input_2);
            
            char input_3[50];
            printf("Enter email of the faculty\n:");
            memset(input_3, 0, sizeof(input_3));
            scanf("%s",input_3);
            input_3[strcspn(input_3, "\n")] = '\0';
            strcpy(faculty.email, input_3);

            char input_4[50];
            printf("Enter Address of the faculty\n:");
            memset(input_4, 0, sizeof(input_4));
            scanf("%s",input_4);
            input_4[strcspn(input_4, "\n")] = '\0';
            strcpy(faculty.address, input_4);
        
            char input_5[50];
            printf("Enter designation of the faculty\n:");
            memset(input_5, 0, sizeof(input_5));
            scanf("%s",input_5);
            input_5[strcspn(input_5, "\n")] = '\0';
            strcpy(faculty.designation, input_5);
            
            send(client_socket, &faculty, sizeof(faculty), 0);
            break;
        case 4:
            //char buff[200];
            char key1[20];
            memset(buff, 0, sizeof(buff));
            recv(client_socket,buff,sizeof(buff),0);
            printf("%s",buff);
            scanf("%s",key1);
            key1[strcspn(key1, "\n")] = '\0';
            send(client_socket,key1,sizeof(key1),0);

            struct Faculty facinfo;
            recv(client_socket,&facinfo,sizeof(struct Faculty),0);
            send(client_socket,"ok",2,0);
            printf("ID:%s\n",facinfo.id);
            printf("password:%s\n",facinfo.password);
            printf("name:%s\n",facinfo.name);
            printf("Email:%s\n",facinfo.email);
            printf("Address:%s\n",facinfo.address);
            printf("Designation :%s\n",facinfo.designation);
            printf("Department:%s\n",facinfo.department);
          
            break;

        case 5:
            char ac_buff[50];
            recv(client_socket,ac_buff,sizeof(ac_buff),0);
            printf("%s\n",ac_buff);
            char act_id[50];
            char act_id1[50];
            scanf("%s",act_id);
            send(client_socket,act_id,sizeof(act_id),0);
            recv(client_socket,act_id1,sizeof(act_id1),0);
            printf("%s\n",act_id1);
            send(client_socket,"Ok",5,0);
            break;
        case 6:
            char ac_buff1[50];
            recv(client_socket,ac_buff1,sizeof(ac_buff1),0);
            printf("%s\n",ac_buff1);
            char act_id_[50];
            char act_id1_[50];
            scanf("%s",act_id_);
            send(client_socket,act_id_,sizeof(act_id_),0);
            recv(client_socket,act_id1_,sizeof(act_id1_),0);
            printf("%s\n",act_id1_);
            send(client_socket,"Ok",5,0);
            break;
        case 7:
            char toupdate[50];
            recv(client_socket,toupdate,sizeof(toupdate),0);
            char inp[50];
            printf("%s\n",toupdate);
            scanf("%s",inp);
            send(client_socket,inp,sizeof(inp),0);

            char DATA1[1000];
            recv(client_socket,DATA1,sizeof(DATA1),0);
            printf("%s\n",DATA1);
            int choice1[1];
            scanf("%d",&choice1[0]);
            send(client_socket,choice1,sizeof(choice1),0);

            char DATA[100];
            recv(client_socket,DATA,sizeof(DATA),0);
            printf("%s\n",DATA);
       
            char DATA2[100];
            scanf("%s",DATA2);
            send(client_socket,DATA2,sizeof(DATA2),0);

            char ackn[10];
            recv(client_socket,ackn,sizeof(ackn),0);
            send(client_socket,"OK",5,0);
            break;
        case 9:
            *admin_exit1 = 1;
            break;
        default:
            // Invalid choice
            send(client_socket, "Invalid choice.\n", 16, 0);
            break;
    }

    return;

}