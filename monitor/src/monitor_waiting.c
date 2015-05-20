#include "monitor_waiting.h"
#include "reg_setting.h"
//monitor suspend the execution of all variants when system call envoked
//here fourth argument position used to check system call entry or exit
// position = SYS_CALL_ENTRY for system call envoke
// position = SYS_CALL_EXIT for system call exit

int monitor_waiting(int variant_count,int *child,int *orig_rax,int position)
{
  int i;
  int k;
  int status;
  int *pid=malloc((variant_count)*(sizeof(int)));
  for(i=0;i<variant_count;i++)
  { 
    pid[i]=wait(&status);
  }
  if(position==SYS_CALL_ENTRY)
  {
    if(WIFEXITED(status))
    {
      for(i=0;i<variant_count;i++)
        kill(child[i],SIGKILL);
      return 1;
    }
    else if(WIFSIGNALED(status))
    {
      for(i=0;i<variant_count;i++)
        kill(child[i],SIGKILL);
      return 2;
    }
    else if(WCOREDUMP(status))
    {
      for(i=0;i<variant_count;k++)
        kill(child[k],SIGKILL);
      return 3;
    }
    else if(WIFSTOPPED(status)&&(WSTOPSIG(status)==11||WSTOPSIG(status)==7))
    {
      for(i=0;i<variant_count;i++)
        kill(child[i],SIGKILL);
      return 4;
    }
    for(i=0;i<variant_count;i++)
    { 
      orig_rax[i] = ptrace(PTRACE_PEEKUSER,child[i], 8 * ORIG_RAX,NULL);
    }
  }
  return 0;
}
