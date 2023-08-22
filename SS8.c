#include <stdio.h>
#include<stdlib.h>
#include <unistd.h>

#define max_line_length 100
int main(int argv,char *args[]){
    char S[100];
    FILE *text = fopen(args[1],"r");
    if(text == NULL){
        return 1;
    }
    while(fgets(S,max_line_length,text)) //reads a line from the specified stream and stores it into the string pointed to by str. It stops when either (n-1) characters are read, the newline character is read, or the end-of-file is reached, whichever comes first.
    {
        printf(S);
        printf("\n");
        sleep(2);
    }
    fclose(text);
}