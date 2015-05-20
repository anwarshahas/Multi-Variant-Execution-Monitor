#include "sys_calls_exec_mode.h"

//function exec_by_only_monitor() execute the corresponding system call by monitor only and all variants skip the system call
void exec_by_only_monitor(int variant_count,int* child,struct user_regs_struct* regs,int ret)
{
	set_dummy_sys_call(variant_count,regs);
    set_registers(variant_count,child,regs);
    sys_call_continue(variant_count,child);
    monitor_waiting(variant_count,NULL,NULL,SYS_CALL_EXIT);
    set_ret_value(variant_count,child,regs,ret);
}

//fucntion exec_by_monitor_and_all_variants execute the system call by monitor and by all variants
void exec_by_monitor_and_all_variants(int variant_count,int* child)
{
	sys_call_continue(variant_count,child);
	monitor_waiting(variant_count,NULL,NULL,SYS_CALL_EXIT);
}

//function exec_by_only_variant() execute the system call by only one variant and pass the results to other variants
void exec_by_only_one_variant(int variant_count,int* child,struct user_regs_struct* regs,int ret)
{
	set_dummy_sys_call_except_0(variant_count,regs);
    set_registers(variant_count,child,regs);
	sys_call_continue(variant_count,child);
	monitor_waiting(variant_count,NULL,NULL,SYS_CALL_EXIT);
	ptrace(PTRACE_GETREGS, child[0],NULL, &regs[0]);
	set_ret_value(variant_count,child,regs,regs[0].rax);
}

//function exec_by_all_variants() execute the system call by all variants
void exec_by_all_variants(int variant_count,int* child)
{
	sys_call_continue(variant_count,child);
	monitor_waiting(variant_count,NULL,NULL,SYS_CALL_EXIT);
}