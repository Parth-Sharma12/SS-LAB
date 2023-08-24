# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
int main()
{
 extern char **environ;
 int i=0;
 while(environ[i]) 
 {
  printf("%s\n",environ[i++]);
 }

}
