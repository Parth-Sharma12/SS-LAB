
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
int main()
{
	pid_t pid;
	int pipe_fd[2];
	// creating a pipe
	if((pipe(pipe_fd))==-1)
	{
		perror("ERROR:");
	}
    if((pid=fork())==-1)
    {
    	perror("ERROR:");
    }
    if(pid == 0)
    {   
    	close(pipe_fd[0]);
    	// duplicating write end
    	int fd1 = fcntl(pipe_fd[1],F_DUPFD,0);
        // closing write end
        close(pipe_fd[1]);
        // duplicating standard output to write end
        dup2(fd1,STDOUT_FILENO);
        //executing ls -l
        execlp("ls","ls","-l",NULL);
    }
    else
    {
    	close(pipe_fd[1]);
    	//duplicating read end
    	int fd2 = fcntl(pipe_fd[0],F_DUPFD,0);
    	// closing read end
    	close(pipe_fd[0]);
    	// redirecting std_in to read end
    	dup2(fd2,STDIN_FILENO);
    	// executing wc
    	execlp("wc","wc",NULL);
    }

}
