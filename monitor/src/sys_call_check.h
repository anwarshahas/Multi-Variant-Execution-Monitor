#include "basic_header.h"
#include "sys_calls.h"

#ifndef SYS_CALL_CHECK_   /* Include guard */
#define SYS_CALL_CHECK_

void system_call_checking(int*,int,int*,struct user_regs_struct*);
#endif // SYS_CALL_CHECK_