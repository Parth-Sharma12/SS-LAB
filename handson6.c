#include<stdio.h>
#include<unistd.h>
int main(){
	int nread;
	char ch[50];
	nread=read(0,ch,10); // Reading on STDIN
	write(1,ch,nread);  //Writing on STDOUT
}
