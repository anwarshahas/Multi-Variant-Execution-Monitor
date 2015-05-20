#include "read_string.h"

char *read_string(pid_t child, unsigned long addr) 
{
    char *val = malloc(4096);
    int allocated = 4096;
    int read = 0;
    unsigned long tmp;
    while (1) 
    {
        if (read + sizeof tmp > allocated) 
        {
            allocated *= 2;
            val = realloc(val, allocated);
        }
        tmp = ptrace(PTRACE_PEEKDATA, child, addr + read);
        if(errno != 0) 
        {
            val[read] = 0;
            break;
        }
        memcpy(val + read, &tmp, sizeof tmp);
        if (memchr(&tmp, 0, sizeof tmp) != NULL)
            break;
        read += sizeof tmp;
    }
    return val;
}

