#include "basic_header.h"
#include "monitor_waiting.h"
#ifndef SYS_CALLS_EXEC_MODE_   /* Include guard */
#define SYS_CALLS_EXEC_MODE_

void exec_by_only_monitor(int,int*,struct user_regs_struct*,int);
void exec_by_monitor_and_all_variants(int,int*);
void exec_by_only_one_variant(int,int*,struct user_regs_struct*,int);
void exec_by_all_variants(int,int*);
#endif // SYS_CALLS_EXEC_MODE_