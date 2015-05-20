#include "reg_setting.h"
#include "monitor_waiting.h"
int i;
//function get_registers() store the register value set of variants into 'regs' 
void get_registers(int variant_count,int* child,struct user_regs_struct *regs)
{
	for(i=0;i<variant_count;i++)
    {
    	ptrace(PTRACE_GETREGS, child[i],NULL, &regs[i]);
    }
}

//function sys_call_continue() resume the execution of variants
void sys_call_continue(int variant_count,int* child)
{
	for(i=0;i<variant_count;i++)
    ptrace(PTRACE_SYSCALL,child[i],NULL,NULL);
}


//function set_dummy_sys_call() put a dummy system call number while system call is executed only by monitor (system call skipping)
void set_dummy_sys_call(int variant_count,struct user_regs_struct* regs)
{
	for(i=0;i<variant_count;i++)
    regs[i].orig_rax=SYS_getppid;
}

//function set_dummy_sys_call_except_0() put a dummy system call number while system call is executed only by single variant (system call skipping)
void set_dummy_sys_call_except_0(int variant_count,struct user_regs_struct* regs)
{
  for(i=1;i<variant_count;i++)
    regs[i].orig_rax=SYS_getppid;
}


//function set_registers() set the register value set of variants permenently after changing any register value
void set_registers(int variant_count,int* child,struct user_regs_struct* regs)
{
	for(i=0;i<variant_count;i++)
    ptrace(PTRACE_SETREGS,child[i],NULL,&regs[i]); 
}

//function set_ret_value() set the return value of a system call when it is  skipped by monitor   
void set_ret_value(int variant_count,int* child,struct user_regs_struct* regs,int ret)
{
	for(i=0;i<variant_count;i++)
	{//problem here ptrace_getregisters
  	ptrace(PTRACE_GETREGS, child[i],NULL, &regs[i]);
  	regs[i].rax=ret;
  	ptrace(PTRACE_SETREGS,child[i],NULL,&regs[i]);
	}
}
/*
void set_arg_value(int variant_count,int* child,struct user_regs_struct* regs,int ret)
{
  for(i=0;i<variant_count;i++)
  {
    ptrace(PTRACE_GETREGS,child[i],NULL,&regs[i]);
    write_string(child,)
  }
}
*/

//function by_pass_initial_sys_call() used to by pass initial system call while the process execution statup(library linking etc..)
void by_pass_initial_sys_calls(int variant_count,int* child)
{
  int init_sys_call=20;
  while(init_sys_call>=1)
  {
    monitor_waiting(variant_count,NULL,NULL,5);
    sys_call_continue(variant_count,child);
    monitor_waiting(variant_count,NULL,NULL,5);
    sys_call_continue(variant_count,child);
    init_sys_call--;
  }
}


void register_back_up(int variant_count,int *child,struct user_regs_struct* back_up_regs)
{
  get_registers(variant_count,child,back_up_regs);
}