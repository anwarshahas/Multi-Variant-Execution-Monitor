#include "required_header.h"

int main(int argc,char **argv)
{

  /*function:initialization() from init.c which check 
  (1) given directory path is valid or not ,
  (2) count the no. of executable in given directory and return into variant_count
  */
  int variant_count=initialization(argc,argv);
  //array 'child' for storing pid of variants
  int *child=malloc((variant_count)*(sizeof(int)));
  // array 'orig_rax' for storing system call no.s envoke by vairants
  int *orig_rax=malloc((variant_count)*(sizeof(long)));
  // array 'regs' for storing register value set of each variants
  struct user_regs_struct *regs=malloc((variant_count)*(sizeof(struct user_regs_struct)));
  //integer 'flag' value non-zero shows variants are terminated by some reasons   
  int flag;
  /*function:variants_calling() from variants.c which do
  (1) fork the monitor and execute the variants as child of monitor
  */
  variants_calling(argv,child);
  //by_pass_initial_sys_calls(variant_count,child);
  
  while(1) 
  {
    //wait the monitor untill system call/signal envoke by all variants
    //function:monitor_waiting() from monitor_waiting.c will do
    //(1) wait the monitor
    //(2) check whether it is signal or system call
    //(3) store the system call no. into orig_rax and set return value zero which set flag, if it is system call
    //(4) return non-zero value in the case of signal
    flag=monitor_waiting(variant_count,child,orig_rax,SYS_CALL_ENTRY);
    //print(orig_rax,variant_count);
    if(flag!=0)//signal
      break;
    //function:system_call_miss_match() from miss_match.c will do
    //(1) check system call envoke by evry variant shoud be same  
    system_call_miss_match(variant_count,orig_rax,child);
    //function: get_registers() from reg_setting.c will do
    //(1) set the register value set of each variants(identified by 'pid' available in array 'child')into  'regs' 
    get_registers(variant_count,child,regs);
    //functon:system_call_checking() from sys_call_check.c will do
    //(1) identify the system call from system call no.
    //(2) execute the system call based on some protocols   
    system_call_checking(orig_rax,variant_count,child,regs);
    //function:sys_call_continue() from reg_setting.c will do
    //(1) permit the variants for its execution 
    sys_call_continue(variant_count,child);
  }
  //shut down the process accordingly (with warnig in the case attack)
  process_termination(flag);
  return 0;
}