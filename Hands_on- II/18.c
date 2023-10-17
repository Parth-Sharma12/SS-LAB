/*
============================================================================
Name : 18.c
Author : Parth Sharma
Description : Write a program to find out total number of directories on the pwd.
execute ls -l | grep ^d | wc ? Use only dup2.
Date:22th Sep,2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() 
{
        int pipe_ls_grep[2];
        int pipe_grep_wc[2];
        pipe(pipe_ls_grep);
        pipe(pipe_grep_wc); 
        if(!fork())  //Child
        {
            dup2(pipe_ls_grep[1], STDOUT_FILENO);
            close(pipe_ls_grep[0]);  // Close the read end in the child process
            execlp("ls", "ls", "-l", NULL);  //Execute ls -l
        } 
    else 
    {
            dup2(pipe_ls_grep[0], STDIN_FILENO);
            close(pipe_ls_grep[1]);  // Close the write end in the parent process
            if(!fork())  //child
        {
                    dup2(pipe_grep_wc[1], STDOUT_FILENO);
                    close(pipe_grep_wc[0]);  // Close the read end in the child process
                    execlp("grep", "grep", "^d", NULL);
            } 
        else 
        {
                    dup2(pipe_grep_wc[0], STDIN_FILENO);
                    close(pipe_grep_wc[1]);  // Close the write end in the parent process
                    execlp("wc", "wc", "-l", NULL);
            }   
        }
    return 0;
}
