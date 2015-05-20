#include "init.h"

//function variants_calling() fork the process to create child processes and execute the variants as child processes which given by directoroy path
void variants_calling(char **argv,int *child)
{
	DIR *d;
	struct dirent *dir;
	int i=0;
	d=opendir(argv[1]);
	if(d)
	{
  	char *root=malloc((strlen(argv[1])+2)*sizeof(char));
  	while((dir = readdir(d)) != NULL)
  	{
  		strcpy(root,argv[1]);
      strcat(root,"/");
  		if(strncmp(dir->d_name,".",1)==0||strncmp(dir->d_name,"..",2)==0)
    		continue;
  		child[i]=fork();
  		if(child[i]==0)
    	{
    		ptrace(PTRACE_TRACEME, 0, NULL, NULL);
    		execl(strcat(root,dir->d_name),dir->d_name,argv[2],argv[3],argv[4],NULL);
    	}
  		i++;      
  	}
  	closedir(d);
	}
	return;
}