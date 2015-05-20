#include "basic_header.h"

#ifndef REG_SETTING_   /* Include guard */
#define REG_SETTING_

void get_registers(int,int*,struct user_regs_struct*);
void sys_call_continue(int,int*);
void set_dummy_sys_call(int,struct user_regs_struct*);
void set_dummy_sys_call_except_0(int,struct user_regs_struct*);
void set_registers(int file_count,int*,struct user_regs_struct*);
void set_ret_value(int,int*,struct user_regs_struct*,int);
void by_pass_initial_sys_calls(int,int*);
void register_back_up(int,int*,struct user_regs_struct*);
#endif // REG_SETTING_