#include "basic_header.h"
#include "reg_setting.h"
#include "monitor_waiting.h"

#ifndef SHARED_MEMORY_H_   /* Include guard */
#define SHARED_MEMORY_H_

char *shm_create_by_monitor(pid_t);
char **shm_create(int,int*);
char *master_shm_create(int);
void shmget(int,int*,struct user_regs_struct*,key_t*);
void shmat(int,int*,struct user_regs_struct*,int);
void code_injection_for_shm(int,int *,struct user_regs_struct*);
void code_injection_for_master_shm(int,int *,struct user_regs_struct*);
void monitor_variant_shm_creation(int,int*,struct user_regs_struct*);
#endif // SHARED_MEMORY_H_
