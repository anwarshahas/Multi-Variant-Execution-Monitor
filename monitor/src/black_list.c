#include "black_list.h"

void black_list(char* exec_file)
{
	FILE* fd;
	char str[100];
	fd=fopen("black_list.dat","r");
	while(fscanf(fd,"%s",str)!=EOF)
	{
		if(strcmp(exec_file,str)==0)
		{
			printf("executing confidentials\n");
			break;
		}
	}
}