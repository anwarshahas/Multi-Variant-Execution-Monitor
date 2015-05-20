#include "../sys_calls.h"
#include "../reg_setting.h"
#include "../monitor_waiting.h"
#include "../sys_calls_exec_mode.h"

	int status;
	int ret;
	int i;
	int pid;

void sys_write(int variant_count,int* child,struct user_regs_struct* regs)
{
    for(i=1;i<variant_count;i++)
    {
    	if((regs[0].rdi!=regs[i].rdi)||(strcmp(read_string(child[0],regs[0].rsi),read_string(child[i],regs[i].rsi)))!=0||(regs[0].rdx!=regs[i].rdx))
            //function arg_miss_match() check arguments of system call same or not
            //function from miss_match.c 
        	arg_miss_match(variant_count,child);
    }
    //function read_string() read string from variant memeory
    //function from read_string.c 
    char *temp=read_string(child[0],regs[0].rsi);
    ret=write(regs[0].rdi,temp,regs[0].rdx);
    //function exec_by_only_monitor() skip the variant system call
    //function from sys_calls_exec_mode.c                      
    exec_by_only_monitor(variant_count,child,regs,ret);

}


void sys_read(int variant_count,int* child,struct user_regs_struct* regs)
{
    for(i=1;i<variant_count;i++)
    {
        if(regs[0].rdi!=regs[i].rdi)
        	arg_miss_match(variant_count,child);
    }
    if(regs[0].rdi==0)
    {
        char *buffer= malloc(4096);
        ret=read(0,buffer,4096);
        for(i=0;i<variant_count;i++)
        	write_string(child[i],regs[i].rsi,buffer,ret);
        exec_by_only_monitor(variant_count,child,regs,ret);
    }
    else
    {
        exec_by_all_variants(variant_count,child);
    }
}

void sys_chdir(int variant_count,int* child,struct user_regs_struct* regs)
{
	for(i=1;i<variant_count;i++)
    {
        if((strcmp(read_string(child[0],regs[0].rdi),read_string(child[i],regs[i].rdi)))!=0)
        	arg_miss_match(variant_count,child);                   
    }
    ret=chdir(read_string(child[0],regs[0].rdi));
    exec_by_monitor_and_all_variants(variant_count,child);
}

void sys_getpid(int variant_count,int* child,struct user_regs_struct* regs)
{
    exec_by_only_one_variant(variant_count,child,regs,ret);
}


void sys_getppid(int variant_count,int* child,struct user_regs_struct* regs)
{
	exec_by_all_variants(variant_count,child);
}

void sys_mkdir(int variant_count,int* child,struct user_regs_struct* regs)
{
	for(i=1;i<variant_count;i++)
    {
        if(((strcmp(read_string(child[0],regs[0].rdi),read_string(child[i],regs[i].rdi)))!=0)||(regs[0].rsi!=regs[i].rsi))
        	arg_miss_match(variant_count,child);                    
    }
    ret=mkdir(read_string(child[0],regs[0].rdi),regs[0].rsi);
    exec_by_only_monitor(variant_count,child,regs,ret);
}

void sys_rmdir(int variant_count,int* child,struct user_regs_struct* regs)
{
	for(i=1;i<variant_count;i++)
    {
        if((strcmp(read_string(child[0],regs[0].rdi),read_string(child[i],regs[i].rdi)))!=0)
        	arg_miss_match(variant_count,child);                    
    }
    ret=rmdir(read_string(child[0],regs[0].rdi));
	exec_by_only_monitor(variant_count,child,regs,ret);
}


void sys_chmod(int variant_count,int* child,struct user_regs_struct* regs)
{
	for(i=1;i<variant_count;i++)
    {
        if(((strcmp(read_string(child[0],regs[0].rdi),read_string(child[i],regs[i].rdi)))!=0)||(regs[0].rsi!=regs[i].rsi))
        	arg_miss_match(variant_count,child);  
    }
    ret=chmod(read_string(child[0],regs[0].rdi),regs[0].rsi);
    exec_by_only_monitor(variant_count,child,regs,ret);
}

void sys_create(int variant_count,int* child,struct user_regs_struct* regs)
{
	for(i=1;i<variant_count;i++)
    {
        if(((strcmp(read_string(child[0],regs[0].rdi),read_string(child[i],regs[i].rdi)))!=0)||(regs[0].rsi!=regs[i].rsi))
        	arg_miss_match(variant_count,child);  
    }
    ret=creat(read_string(child[0],regs[0].rdi),regs[0].rsi);
    exec_by_only_monitor(variant_count,child,regs,ret);
}

void sys_open(int variant_count,int* child,struct user_regs_struct* regs)
{
    /*
	for(i=1;i<variant_count;i++)
    {
        if(((strcmp(read_string(child[0],regs[0].rdi),read_string(child[i],regs[i].rdi)))!=0)||(regs[0].rsi!=regs[i].rsi)||(regs[0].rdx!=regs[i].rdx))
        	arg_miss_match(variant_count,child);  
    }
*/
    if((regs[0].rsi==(O_RDONLY|O_CLOEXEC))||(regs[0].rsi==O_RDONLY))
    {
      	exec_by_all_variants(variant_count,child);
    }
    else
    {
        ret=open(read_string(child[0],regs[0].rdi),regs[0].rsi,regs[0].rdx);
      	exec_by_only_monitor(variant_count,child,regs,ret);
    }
}


void sys_close(int variant_count,int* child,struct user_regs_struct* regs)
{
	 for(i=1;i<variant_count;i++)
    {
        if(regs[0].rdi!=regs[i].rdi)
        	arg_miss_match(variant_count,child); 
    }
/*
    ret=close(regs[0].rdi);
    if(ret==-1)
    {
*/
      	exec_by_all_variants(variant_count,child);
/*
    }
    else
    {

	   exec_by_only_monitor(variant_count,child,regs,ret);
    }
*/
}

void sys_rename(int variant_count,int* child,struct user_regs_struct* regs)
{
	for(i=1;i<variant_count;i++)
    {
        if(((strcmp(read_string(child[0],regs[0].rdi),read_string(child[i],regs[i].rdi)))!=0)||(strcmp(read_string(child[0],regs[0].rsi),read_string(child[i],regs[i].rsi)))!=0)
        	arg_miss_match(variant_count,child); 
    }

    ret=rename(read_string(child[0],regs[0].rdi),read_string(child[0],regs[0].rsi));
    exec_by_only_monitor(variant_count,child,regs,ret);
}

void sys_getuid(int variant_count,int* child,struct user_regs_struct* regs)
{
	exec_by_all_variants(variant_count,child);
}

void sys_time(int variant_count,int* child,struct user_regs_struct* regs)
{
    exec_by_only_one_variant(variant_count,child,regs,ret);
    for(i=1;i<variant_count;i++)
    {
        write_string(child[i],regs[i].rdi,regs[0],sizeof(time_t));
    }
    set_registers(variant_count,child,regs);
}


void sys_chown(int variant_count,int* child,struct user_regs_struct* regs)
{
    for(i=1;i<variant_count;i++)
    {
        if((regs[0].rsi!=regs[i].rsi)||(strcmp(read_string(child[0],regs[0].rdi),read_string(child[i],regs[i].rdi)))!=0||(regs[0].rdx!=regs[i].rdx))
            //function arg_miss_match() check arguments of system call same or not
            //function from miss_match.c 
            arg_miss_match(variant_count,child);
    }
    //function read_string() read string from variant memeory
    //function from read_string.c 
    char *temp=read_string(child[0],regs[0].rdi);
    ret=chown(temp,regs[0].rdi,regs[0].rdx);
    //function exec_by_only_monitor() skip the variant system call
    //function from sys_calls_exec_mode.c                      
    exec_by_only_monitor(variant_count,child,regs,ret);
}

//add new prefix for fstat stat lstat

void sys_fstat(int variant_count,int* child,struct user_regs_struct* regs)
{
    for(i=1;i<variant_count;i++)
    {
        if(regs[0].rdi!=regs[i].rdi)
            //function arg_miss_match() check arguments of system call same or not
            //function from miss_match.c 
            arg_miss_match(variant_count,child);
    }
    exec_by_all_variants(variant_count,child);
}

void sys_stat(int variant_count,int* child,struct user_regs_struct* regs)
{
    for(i=1;i<variant_count;i++)
    {
        if(strcmp(read_string(child[0],regs[0].rdi),read_string(child[i],regs[i].rdi))!=0)
            //function arg_miss_match() check arguments of system call same or not
            //function from miss_match.c 
            arg_miss_match(variant_count,child);
    }
    exec_by_all_variants(variant_count,child);
}

void sys_lstat(int variant_count,int* child,struct user_regs_struct* regs)
{
    for(i=1;i<variant_count;i++)
    {
        if(strcmp(read_string(child[0],regs[0].rdi),read_string(child[i],regs[i].rdi))!=0)
            //function arg_miss_match() check arguments of system call same or not
            //function from miss_match.c 
            arg_miss_match(variant_count,child);
    }
    exec_by_all_variants(variant_count,child);
}

void sys_lseek(int variant_count,int* child,struct user_regs_struct* regs)
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

void sys_mmap(int variant_count,int* child,struct user_regs_struct* regs)
{
    //right now we are not checking argument comparison :: future work
    exec_by_all_variants(variant_count,child);
}

void sys_munmap(int variant_count,int* child,struct user_regs_struct* regs)
{
    //right now we are not checking argument comparison :: future work
    exec_by_all_variants(variant_count,child);
}