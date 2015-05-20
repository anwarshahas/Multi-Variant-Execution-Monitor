#include<stdio.h>
int main()
{
	int a,b;
	a=getppid();
	printf("ppid is %d\n",a);
	b=getpid();
	printf("pid is %d\n",b);
}