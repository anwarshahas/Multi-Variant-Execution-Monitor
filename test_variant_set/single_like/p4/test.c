#include<stdio.h>
int main()
{
	char* buffer=malloc(4096);
	printf("Enter the stirng....\n");
	read(0,buffer,4096);
	printf("%s\n",buffer);
}