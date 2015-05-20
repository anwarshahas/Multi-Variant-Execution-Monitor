#include "miss_match.h"
#include "color.h"

//if system call envoke by variants are differ then kill variants
void system_call_miss_match(int variant_count,int *orig_rax,int* child)
{
  int j;
  int i;
  for(i=1;i<variant_count;i++)
  {
    if(orig_rax[0]!=orig_rax[i])
    {
      printf(ANSI_COLOR_CYAN  "System call miss match (on system call no. %d   %d)\n" ANSI_COLOR_RESET,orig_rax[0],orig_rax[i]);   
      for(j=0;j<variant_count;j++)
        kill(child[j],SIGKILL);
      printf(ANSI_COLOR_RED "Attack detected::Execution stopped\nMonitor is shutting Down due to attack detection\n" ANSI_COLOR_RESET);
      exit(1);              
    }
  }
}

//if system call arguments of variants are differ then kill variants
void arg_miss_match(int variant_count,int* child)
{
  printf(ANSI_COLOR_CYAN "System call miss match by args\n"ANSI_COLOR_RESET);
  int j;
  for(j=0;j<variant_count;j++)
    kill(child[j],SIGKILL);
  printf(ANSI_COLOR_RED "Attack detected::Execution stopped\nMonitor is shutting Down due to attack detection\n" ANSI_COLOR_RESET);
  exit(1); 
}