#include<stdio.h>
int main()
{
	chdir("/home/shahas/Desktop/");
	mkdir("new_dir1",0777);
	chdir("new_dir1");
	creat("database.txt",0777);
}