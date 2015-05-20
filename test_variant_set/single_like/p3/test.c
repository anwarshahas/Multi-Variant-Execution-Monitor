#include<stdio.h>
int main()
{
	int a;
	
	a=chdir("/home/shahas/Desktop/");
	if(a==0)
		printf("Directory changed successfully\n");
	a=mkdir("new_dir1",0777);
	if(a==0)
		printf("New Directory created successfully\n");
	a=chdir("new_dir1");
	if(a==0)
		printf("Directory changed successfully\n");
	a=creat("file.txt",0777);
	if(a>=0)
		printf("file.txt created successfully\n");
}