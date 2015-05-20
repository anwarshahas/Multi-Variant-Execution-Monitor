#include "basic_header.h"

#ifndef SYS_CALLS_1_20_   /* Include guard */
#define SYS_CALLS_1_20_
void sys_write(int,int*,struct user_regs_struct*);
void sys_read(int,int*,struct user_regs_struct*);
void sys_chdir(int,int*,struct user_regs_struct*);
void sys_getpid(int,int*,struct user_regs_struct*);
void sys_getppid(int,int*,struct user_regs_struct*);
void sys_mkdir(int,int*,struct user_regs_struct*);
void sys_rmdir(int,int*,struct user_regs_struct*);
void sys_chmod(int,int*,struct user_regs_struct*);
void sys_create(int,int*,struct user_regs_struct*);
void sys_open(int,int*,struct user_regs_struct*);
void sys_close(int,int*,struct user_regs_struct*);
void sys_rename(int,int*,struct user_regs_struct*);
void sys_getuid(int,int*,struct user_regs_struct*);
void sys_time(int,int*,struct user_regs_struct*);
void sys_chown(int,int*,struct user_regs_struct*);
void sys_fstat(int,int*,struct user_regs_struct*);
void sys_stat(int,int*,struct user_regs_struct*);
void sys_lstat(int,int*,struct user_regs_struct*);
void sys_lseek(int,int*,struct user_regs_struct*);
void sys_mmap(int,int*,struct user_regs_struct*);
void sys_munmap(int,int*,struct user_regs_struct*);
void sys_execve(int,int*,struct user_regs_struct*);
void sys_mprotect(int,int*,struct user_regs_struct*);
void sys_socket(int,int*,struct user_regs_struct*);
void sys_accept(int,int*,struct user_regs_struct*);
void sys_connect(int,int*,struct user_regs_struct*);
void sys_bind(int,int*,struct user_regs_struct*);
void sys_listen(int,int*,struct user_regs_struct*);
void sys_rest(int,int*,struct user_regs_struct*);
void sys_setsockopt(int,int*,struct user_regs_struct*);
void sys_getsockname(int,int*,struct user_regs_struct*);
void sys_sendto(int,int*,struct user_regs_struct*);
void sys_recvmsg(int,int*,struct user_regs_struct*);
void sys_futex(int,int*,struct user_regs_struct*);
void sys_brk(int,int*,struct user_regs_struct*);
void ssys_poll(int,int*,struct user_regs_struct*);
void sys_rt_sigaction(int,int*,struct user_regs_struct*);
void ys_rt_sigprocmask(int,int*,struct user_regs_struct*);
void sys_rt_sigreturn(int,int*,struct user_regs_struct*);
void sys_ioctl(int,int*,struct user_regs_struct*);

#endif // SYS_CALLS_1_20_