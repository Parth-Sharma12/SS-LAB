#include<stdlib.h>
#include<unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
struct student student;

void process_course_id(int ID,char* login,int client_socket){
    int course_file = open("course.txt",O_RDWR);
    struct course course_;
    while (read(course_file,&course_,sizeof(struct course))) {
        if(course_.id == ID){
            if(course_.seats>0){
                lseek(course_file,-(sizeof(struct course)),SEEK_CUR);
                struct course updatecpy;
                updatecpy.id=ID;
                updatecpy.actv = course_.actv;
                updatecpy.Max_Seats = course_.Max_Seats;
                strcpy(updatecpy.faculty_id,course_.faculty_id);
                strcpy(updatecpy.faculty_name,course_.faculty_name);
                strcpy(updatecpy.name,course_.name);
                strcpy(updatecpy.code,course_.code);
                updatecpy.seats = course_.seats - 1; //Updating available seats
                write(course_file,&updatecpy,sizeof(struct course));
                send(client_socket,"Successfully enrolled",sizeof("Successfully enrolled"),0);

                int enr = open("course_enrolled.txt",O_RDWR);// SAVING INFORMATION OF THE COURSE ENROLLED
                struct course_enrolled c_enr;
                c_enr.actv = 1;  //Means still enrolled
                strcpy(c_enr.student_id,login);
                c_enr.course_id = course_.id;
                c_enr.drop = 0;
                strcpy(c_enr.name,course_.name);
                strcpy(c_enr.faculty_name,course_.faculty_name);
                strcpy(c_enr.code,course_.code);
                lseek(enr,0,SEEK_END);
                write(enr,&c_enr,sizeof(struct course_enrolled));
                close(enr);
            }
            else{
                send(client_socket,"Sorry No seat available",sizeof("Sorry No seat available"),0);
            }
            char rev[5];
            recv(client_socket,rev,sizeof(rev),0);
        }
    }
    close(course_file);
}
void Denroll(int ID,char* login,int client_socket){
    int _file = open("course.txt",O_RDWR);
    lseek(_file,0,SEEK_SET);
    struct course course_;
    while (read(_file,&course_,sizeof(struct course))) {
        if(course_.id == ID){
            if(course_.seats<course_.Max_Seats){
                lseek(_file,-(sizeof(struct course)),SEEK_CUR);
                struct course updatecpy;
                updatecpy.id=course_.id;
                updatecpy.actv = course_.actv;
                updatecpy.Max_Seats = course_.Max_Seats;
                strcpy(updatecpy.faculty_id,course_.faculty_id);
                strcpy(updatecpy.faculty_name,course_.faculty_name);
                strcpy(updatecpy.name,course_.name);
                strcpy(updatecpy.code,course_.code);
                updatecpy.seats = course_.seats + 1; //Updating available seats
                write(_file,&updatecpy,sizeof(struct course));
                send(client_socket,"Successfully Denrolled",sizeof("Successfully Denrolled"),0);

                int enr = open("course_enrolled.txt",O_RDWR);// SAVING INFORMATION OF THE COURSE ENROLLED
                struct course_enrolled c_enr;
                while(read(enr,&c_enr,sizeof(struct course_enrolled))){
                    if(c_enr.course_id == ID){
                        lseek(enr,-(sizeof(struct course_enrolled)),SEEK_CUR);
                        c_enr.drop = 1;
                        write(enr,&c_enr,sizeof(struct course_enrolled));
                        break;
                    }
                }
                close(enr);
                break;
            }
            else{
                send(client_socket,"Sorry You cannot denroll",sizeof("Sorry You cannot denroll"),0);
                break;
            }
            
        }
    }
    char rev[5];
    recv(client_socket,rev,sizeof(rev),0);
    close(_file);
}


int searchStudentByID(char *ID,int client_socket,char *password,int br) {
        int file = open("student_data.txt", O_RDONLY);
        
        struct student studentinfo;
        int found = 0; // Flag to check if the student was found
        while (read(file,&studentinfo,sizeof(struct student))) { // Read ID and check if successfull
        int ver[2];
        if (strcmp(studentinfo.id,ID)==0) {
        // Student found, print their information
            if(strcmp(studentinfo.password,password)==0){
                ver[0] = 0;
                char buff_[5];
                send(client_socket,ver,sizeof(ver),0);
                recv(client_socket,buff_,sizeof(buff_),0);
                break;
            }
            else{
                ver[0] = 1;         
                send(client_socket,ver,sizeof(ver),0);
                char buff_[5];
                recv(client_socket,buff_,sizeof(buff_),0);
                br = 1;
                break;
            }
        }
    }
    close(file);
    return br;
}
void performStudent_Task(int choice, int client_socket,char* login,int *student_exit) {
    switch (choice) {
        case 1: //View Offering courses
            int file = open("course.txt",O_RDONLY);
            struct course course;
            while (read(file,&course,sizeof(struct course))) { // Read ID and check if successful
                if(course.actv==1){
                    send(client_socket,"Start",6,0);
                    char repl1[5];
                    memset(repl1, 0, sizeof(repl1));
                    recv(client_socket,repl1,sizeof(repl1),0);

                    char ack2[5];
                    send(client_socket,&course,sizeof(struct course),0); 
                    recv(client_socket,ack2,sizeof(ack2),0);
                }
            }                   
            send(client_socket,"Done",5,0);
            char repl[5];
            recv(client_socket,repl,sizeof(repl),0);
            close(file);
            break;
        case 2://Enrolling in a course
            int opted[2];
            send(client_socket,"Enter Course ID you want to Enroll in\n",50,0);
            recv(client_socket,opted,sizeof(opted),0);
            process_course_id(opted[0],login,client_socket);
            break;
        case 3:
            int view_enr = open("course_enrolled.txt",O_RDONLY);
            struct course_enrolled course_enr;
            while(read(view_enr,&course_enr,sizeof(struct course_enrolled))){
                if(strcmp(course_enr.student_id,login)==0 && course_enr.drop == 0 && course_enr.actv == 1){
                    char c_rec[5];
                    char c_ack1[5];
                    send(client_socket,"Start",5,0);
                    recv(client_socket,c_ack1,sizeof(c_ack1),0);
                    send(client_socket,&course_enr,sizeof(course_enr),0);
                    recv(client_socket,c_rec,sizeof(c_rec),0);
                }
            }
            close(view_enr);
            char c_ack[5];
            send(client_socket,"Done",5,0);
            recv(client_socket,c_ack,sizeof(c_ack),0);
            break;
        case 4:
            int opted1[2];
            send(client_socket,"Enter Course ID you want to DEnroll \n",50,0);
            recv(client_socket,opted1,sizeof(opted1),0);
            Denroll(opted1[0],login,client_socket);
            break;
        case 5:
            char newpass[50];
            int stu = open("student_data.txt",O_RDWR);
            send(client_socket,"Enter New Password",20,0);
            recv(client_socket,newpass,sizeof(newpass),0);
            struct student stupass;
            int numericId;
            sscanf(login, "MT@%d", &numericId);
            int offset = (numericId-1)*sizeof(struct student);
            lseek(stu,offset,SEEK_SET);
            read(stu,&stupass,sizeof(struct student));
            strcpy(stupass.password,newpass);
            lseek(stu,-(sizeof(struct student)),SEEK_CUR);
            write(stu,&stupass,sizeof(struct student));
            send(client_socket,"Password Changed Successfully\n",20,0);
            char rec1[5];
            recv(client_socket,rec1,sizeof(rec1),0);
            close(stu);
            break;
        case 6:
            *student_exit = 1;
            break;
        default:
            // Invalid choice
            send(client_socket, "Invalid choice.\n", 16, 0);
            break;
    }
    return;
}

//CLIENT SIDE 
void Student(int choice, int client_socket,char* login,int *student_exit1){
        switch (choice) {
        case 1:
            while(1){
            printf("********************************************************************************\n");
            char rec[6];
            memset(rec, 0, sizeof(rec));
            recv(client_socket,rec,sizeof(rec),0);
            send(client_socket,"ok",2,0);
            if(strcmp("Done",rec)==0){
                break;
            }
            struct course course2;
            recv(client_socket,&course2,sizeof(struct course),0);
            send(client_socket,"ok",5,0);
            printf("Faculty_id: %s\n", course2.faculty_id);
            printf("ID: %d\n", course2.id);
            printf("Name: %s\n", course2.name);
            printf("Faculty_name: %s\n", course2.faculty_name);
            printf("Maximum Seats: %d\n", course2.seats);
            printf("Course Code: %s\n", course2.code);   
            printf("********************************************************************\n");        
        }
            break;
        case 2:
            char buff5[50];
            recv(client_socket,buff5,sizeof(buff5),0);
            printf("%s\n",buff5);
            int opt1[2];
            scanf("%d",&opt1[0]); //Entering course id
            send(client_socket,opt1,sizeof(opt1),0);
            char ak1[100];
            recv(client_socket,ak1,sizeof(ak1),0);
            printf("%s\n",ak1);
            send(client_socket,"Ok",5,0);
            break;
        case 3:
            struct course_enrolled course_info1;
            while(1){
                char knw[10];
                recv(client_socket,knw,sizeof(knw),0);
                send(client_socket,"ok",4,0);
                if(strcmp(knw,"Done")==0){
                    break;
                }
                printf("*******************************************************\n");
                recv(client_socket,&course_info1,sizeof(course_info1),0);
                printf("Student_id:%s\n",course_info1.student_id);
                printf("course_id:%d\n",course_info1.course_id);
                printf("name:%s\n",course_info1.name);
                printf("faculty_name:%s\n",course_info1.faculty_name);
                printf("Code:%s\n",course_info1.code);
                send(client_socket,"OK",4,0);
            }
            break;
        case 4:
            char buff51[50];
            recv(client_socket,buff51,sizeof(buff51),0);
            printf("%s\n",buff51);
            int opt11[2];
            scanf("%d",&opt11[0]); //Entering course id
            send(client_socket,opt11,sizeof(opt11),0);
            char ak11[100];
            recv(client_socket,ak11,sizeof(ak11),0);
            printf("%s\n",ak11);
            send(client_socket,"Ok",5,0);
            break;
        case 5:
            char chpass[100];
            recv(client_socket,chpass,sizeof(chpass),0);
            printf("%s\n",chpass);
            char new_pass[50];
            scanf("%s",new_pass);
            send(client_socket,new_pass,sizeof(new_pass),0);
            char success[50];
            recv(client_socket,success,sizeof(success),0);
            printf("%s\n",success);
            send(client_socket,"ok",5,0);
            break;
        case 6:
            *student_exit1 = 1;
            break;
        default:
            // Invalid choice
            send(client_socket, "Invalid choice.\n", 16, 0);
            break;
    }

    return;

}