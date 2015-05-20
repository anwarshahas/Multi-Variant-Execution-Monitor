#include "../sys_calls.h"
#include "../reg_setting.h"
#include "../monitor_waiting.h"
#include "../sys_calls_exec_mode.h"
#include "../black_list.h"

	int status;
	int ret;
	int i;
	int pid;

void sys_execve(int variant_count,int* child,struct user_regs_struct* regs)
{
	
    for(i=1;i<variant_count;i++)
    {
    	//if((strcmp(read_string(child[0],regs[0].rdi),read_string(child[i],regs[i].rdi)))!=0||(strcmp(read_string(child[0],regs[0].rsi),read_string(child[i],regs[i].rsi)))!=0||(strcmp(read_string(child[0],regs[0].rdx),read_string(child[i],regs[i].rdx)))!=0)
        if((strcmp(read_string(child[0],regs[0].rdi),read_string(child[i],regs[i].rdi)))!=0)
        
            //function arg_miss_match() check arguments of system call same or not
            //function from miss_match.c 
        	arg_miss_match(variant_count,child);
    }
    black_list(read_string(child[0],regs[0].rdi));
    //check the exec file which belong to black list or white list 
    //if exec file from white list allow exec system call
    //if exec file from black list deny exec system call
    exec_by_all_variants(variant_count,child);
}

void sys_mprotect(int variant_count,int* child,struct user_regs_struct* regs)
{
	for(i=1;i<variant_count;i++)
    {
        if((strcmp(read_string(child[0],regs[0].rdi),read_string(child[i],regs[i].rdi)))!=0||(regs[0].rsi!=regs[i].rsi)||(regs[0].rdx!=regs[i].rdx))
            //function arg_miss_match() check arguments of system call same or not
            //function from miss_match.c 
            arg_miss_match(variant_count,child);  
    }
    exec_by_all_variants(variant_count,child);
}

void sys_socket(int variant_count,int *child,struct user_regs_struct* regs)
{
	for(i=1;i<variant_count;i++)
    {
        if((regs[0].rdi!=regs[i].rdi)||(regs[0].rsi!=regs[i].rsi)||(regs[0].rdx!=regs[i].rdx))
            //function arg_miss_match() check arguments of system call same or not
            //function from miss_match.c 
            arg_miss_match(variant_count,child);  
    }
    exec_by_all_variants(variant_count,child);
}

void sys_connect(int variant_count,int *child,struct user_regs_struct* regs)
{
	for(i=1;i<variant_count;i++)
    {
        if((regs[0].rdi!=regs[i].rdi)||(regs[0].rdx!=regs[i].rdx))
            //function arg_miss_match() check arguments of system call same or not
            //function from miss_match.c 
            arg_miss_match(variant_count,child);  
    }
    exec_by_only_one_variant(variant_count,child,regs,ret);
}

void sys_accept(int variant_count,int *child,struct user_regs_struct* regs)
{
	for(i=1;i<variant_count;i++)
    {
        if(regs[0].rdi!=regs[i].rdi)
            //function arg_miss_match() check arguments of system call same or not
            //function from miss_match.c 
            arg_miss_match(variant_count,child);  
    }
    exec_by_only_one_variant(variant_count,child,regs,ret);
}

void sys_bind(int variant_count,int *child,struct user_regs_struct* regs)
{
	for(i=1;i<variant_count;i++)
    {
        if((regs[0].rdi!=regs[i].rdi)||(regs[0].rdx!=regs[i].rdx))
            //function arg_miss_match() check arguments of system call same or not
            //function from miss_match.c 
            arg_miss_match(variant_count,child);  
    }
    exec_by_all_variants(variant_count,child);
}

void sys_listen(int variant_count,int *child,struct user_regs_struct* regs)
{
	for(i=1;i<variant_count;i++)
    {
        if((regs[0].rdi!=regs[i].rdi)||(regs[0].rsi!=regs[i].rsi))
            //function arg_miss_match() check arguments of system call same or not
            //function from miss_match.c 
            arg_miss_match(variant_count,child);  
    }
    exec_by_only_one_variant(variant_count,child,regs,ret);
}

void sys_rest(int variant_count,int *child,struct user_regs_struct* regs)
{
    exec_by_all_variants(variant_count,child);
}

void sys_setsockopt(int variant_count,int* child,struct user_regs_struct* regs)
{
    exec_by_only_one_variant(variant_count,child,regs,ret);
}

void sys_getsockname(int variant_count,int* child,struct user_regs_struct* regs)
{
    exec_by_only_one_variant(variant_count,child,regs,ret);
}

void sys_recvmsg(int variant_count,int* child,struct user_regs_struct* regs)
{
    exec_by_all_variants(variant_count,child);
}

void sys_sendto(int variant_count,int* child,struct user_regs_struct* regs)
{
    exec_by_all_variants(variant_count,child);
}

void sys_futex(int variant_count,int* child,struct user_regs_struct* regs)
{
    exec_by_all_variants(variant_count,child);
}

void sys_brk(int variant_count,int* child,struct user_regs_struct* regs)
{
    exec_by_all_variants(variant_count,child);
}

void sys_poll(int variant_count,int* child,struct user_regs_struct* regs)
{
    exec_by_all_variants(variant_count,child);
}

void sys_rt_sigaction(int variant_count,int* child,struct user_regs_struct* regs)
{
    exec_by_all_variants(variant_count,child);
}

void sys_rt_sigprocmask(int variant_count,int* child,struct user_regs_struct* regs)
{
    exec_by_all_variants(variant_count,child);
}

void sys_rt_sigreturn(int variant_count,int* child,struct user_regs_struct* regs)
{
    exec_by_all_variants(variant_count,child);
}

void sys_ioctl(int variant_count,int* child,struct user_regs_struct* regs)
{
    exec_by_all_variants(variant_count,child);
}

