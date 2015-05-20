#include "sys_call_check.h"
#include "monitor_waiting.h"
#include "sys_calls_exec_mode.h"

//identify the system call from system call number and execute the corresponding system call accoriding to type system call
void system_call_checking(int* orig_rax,int variant_count,int* child,struct user_regs_struct* regs)
{
	switch(orig_rax[0])
	{
		case SYS_write:				sys_write(variant_count,child,regs);			break;
		case SYS_read:				sys_read(variant_count,child,regs);				break;
		case SYS_chdir:				sys_chdir(variant_count,child,regs);			break;
		case SYS_getppid:			sys_getppid(variant_count,child,NULL);			break;
		case SYS_getpid:			sys_getpid(variant_count,child,regs);			break;
		case SYS_mkdir:				sys_mkdir(variant_count,child,regs);			break;
		case SYS_rmdir:				sys_rmdir(variant_count,child,regs);			break;
		case SYS_chmod:				sys_chmod(variant_count,child,regs);			break;
		case SYS_creat:				sys_create(variant_count,child,regs);			break;
		case SYS_open:				sys_open(variant_count,child,regs);				break;
		case SYS_close:				sys_close(variant_count,child,regs);			break;
		case SYS_getuid:			sys_getuid(variant_count,child,NULL);			break;
		case SYS_time:				sys_time(variant_count,child,regs);				break;
		case SYS_chown:				sys_chown(variant_count,child,regs);			break;
		case SYS_fstat:				sys_fstat(variant_count,child,regs);			break;
		case SYS_stat:				sys_stat(variant_count,child,regs);				break;
		case SYS_lstat:				sys_lstat(variant_count,child,regs);			break;
		case SYS_lseek:				sys_lseek(variant_count,child,regs);			break;
		case SYS_mmap:				sys_mmap(variant_count,child,regs);				break;
		case SYS_munmap:			sys_munmap(variant_count,child,regs);			break;
		case SYS_execve:			sys_execve(variant_count,child,regs);			break;
		case SYS_mprotect:			sys_mprotect(variant_count,child,regs);			break;
		case SYS_socket:			sys_socket(variant_count,child,regs);			break;
		case SYS_connect:			sys_connect(variant_count,child,regs);			break;
		case SYS_accept:			sys_accept(variant_count,child,regs);			break;
		case SYS_bind:				sys_bind(variant_count,child,regs);				break;
		case SYS_listen:			sys_listen(variant_count,child,regs);			break;
		case SYS_setsockopt:		sys_setsockopt(variant_count,child,regs);		break;
		case SYS_getsockname:		sys_getsockname(variant_count,child,regs);		break;
		case SYS_sendto:			sys_sendto(variant_count,child,regs);			break;
		case SYS_recvmsg:			sys_recvmsg(variant_count,child,regs);			break;
		case SYS_futex:				sys_futex(variant_count,child,regs);			break;
		case SYS_brk:				sys_brk(variant_count,child,regs);				break;
		case SYS_poll:				sys_poll(variant_count,child,regs);				break;
		case SYS_rt_sigaction:		sys_rt_sigaction(variant_count,child,regs);		break;
		case SYS_rt_sigprocmask:	sys_rt_sigprocmask(variant_count,child,regs);	break;
		case SYS_rt_sigreturn:		sys_rt_sigreturn(variant_count,child,regs);		break;
		case SYS_ioctl:				sys_ioctl(variant_count,child,regs);			break;

		//default: 			sys_rest(variant_count,child,regs);		break;
	}

}          	
     		 
  