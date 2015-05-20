#include "shared_memory.h"

char *shm_create_by_monitor(pid_t child)
{
    int shmid;
    key_t key;
    char* data;
    key = child;
    /*
     * Create the segment.
     */
    if((shmid = shmget(key, 1024, IPC_CREAT | 0666)) < 0) 
    {
        perror("shmget");
        exit(1);
    }
    /*
     * Now we attach the segment to our data space.
     */
    if((data = shmat(shmid,NULL, 0)) == (char *) -1) 
    {
        perror("shmat");
        exit(1);
    }
    return data;
}

char **shm_create(int variant_count,int* child)
{
	int i;
	char* memory_segments[variant_count]; 
	for(i=0; i<variant_count; i++)
         memory_segments[i] = malloc(1 * sizeof(char*));
	for(i=0;i<variant_count;i++)
		memory_segments[i] = shm_create_by_monitor(child[i]);
	return memory_segments;
}

char *master_shm_create(int variant_count)
{
	key_t key = 123456789;
	char* data;
	data = shm_create_by_monitor(key);
	return data;
}

void shmget(int variant_count,int *child,struct user_regs_struct* regs,key_t *key)
{
	int i;
	get_registers(variant_count,child,regs);
	for(i=0;i<variant_count;i++)
	{
		regs[i].rax = 29;
		if(key==NULL)
			regs[i].rdi = child[i];
		else
			regs[i].rdi = *key;
		regs[i].rsi = 1024;
		regs[i].rdx = IPC_CREAT | 0666;
	}
	set_registers(variant_count,child,regs);
}

void shmat(int variant_count,int *child,struct user_regs_struct* regs,int* shmid)
{
	int i;
	get_registers(variant_count,child,regs);
	for(i=0;i<variant_count;i++)
	{
		regs[i].rax	= 30;
		regs[i].rdi	= *shmid;
		regs[i].rsi	= NULL;
		regs[i].rdx	= 0;
	}
	set_registers(variant_count,child,regs);
}

void code_injection_for_shm(int variant_count,int *child,struct user_regs_struct* regs)
{
	
	key_t *key=123456789;
	int *shmid=malloc( variant_count * (sizeof(int)));
	int i;
	get_registers(variant_count,child,regs);
	shmget(variant_count,child,regs,key);
	sys_call_continue(variant_count,child);
    monitor_waiting(variant_count,NULL,NULL,SYS_CALL_EXIT);
    sys_call_continue(variant_count,child);
    monitor_waiting(variant_count,NULL,NULL,SYS_CALL_EXIT);
    get_registers(variant_count,child,regs);
    for(i=0;i<variant_count;i++)
    	shmid[i]=regs[i].rax;

    //set IP back to the system call point

    shmat(variant_count,child,regs,shmid);
    sys_call_continue(variant_count,child);
    monitor_waiting(variant_count,NULL,NULL,SYS_CALL_EXIT);
    sys_call_continue(variant_count,child);
    monitor_waiting(variant_count,NULL,NULL,SYS_CALL_EXIT);
}

void code_injection_for_master_shm(int variant_count,int *child,struct user_regs_struct* regs)
{
	int *shmid=NULL;
	int i;
	get_registers(variant_count,child,regs);
	shmget(variant_count,child,regs,key);
	sys_call_continue(variant_count,child);
    monitor_waiting(variant_count,NULL,NULL,SYS_CALL_EXIT);
    sys_call_continue(variant_count,child);
    monitor_waiting(variant_count,NULL,NULL,SYS_CALL_EXIT);
    get_registers(variant_count,child,regs);
    for(i=0;i<variant_count;i++)
    	shmid[i]=regs[i].rax;

    //set IP back to the system call point

    shmat(variant_count,child,regs,shmid);
    sys_call_continue(variant_count,child);
    monitor_waiting(variant_count,NULL,NULL,SYS_CALL_EXIT);
    sys_call_continue(variant_count,child);
    monitor_waiting(variant_count,NULL,NULL,SYS_CALL_EXIT);
}

void monitor_variant_shm_creation(int variant_count,int *child,struct user_regs_struct* regs)
{
	struct user_regs_struct *back_up_regs=malloc((variant_count)*(sizeof(struct user_regs_struct)));
	register_back_up(variant_count,child,back_up_regs);
	char **memory_segments=shm_create(variant_count,child);
	char **master_memory_segment=master_shm_create(variant_count);
	code_injection_for_shm(variant_count,child,regs);
	code_injection_for_master_shm(variant_count,child,regs);
}