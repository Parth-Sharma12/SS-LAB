#include<fcntl.h>

#include<stdio.h>
int main(){
int fd = open("handson3.txt",O_RDONLY);
printf("File Descriptor value: %d",fd);
}
