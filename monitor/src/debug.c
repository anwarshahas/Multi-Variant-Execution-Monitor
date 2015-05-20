#include "debug.h"

void print(int *orig_rax,int file_count)
{
  int i;
  for(i=0;i<file_count;i++)
    printf("%d\t",orig_rax[i]);
  printf("\n");
}