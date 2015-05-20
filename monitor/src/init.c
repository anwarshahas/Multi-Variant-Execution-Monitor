#include "init.h"

	DIR *d;
	struct dirent *dir;
	int file_count=0;

int initialization(int argc,char **argv)
{
	printf("\n\n----------------------Monitor Starting-------------------------\n\n\n");
	//checking input directory is given or not
	if(argc<2)
	{
		printf("Error: Input directory is missing\t%s [path to the directory]\n",argv[0]);
		printf("Program Aborting....\n");
		exit(0);
	}
	d = opendir(argv[1]);
	//checking given directory is valid
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		file_count++; 
		closedir(d);
	}
	else
	{
		printf("Error: Input directory is invalid\n");
		exit(0);
	}
	//return number of variants available in the directory
	return file_count-2;
}
