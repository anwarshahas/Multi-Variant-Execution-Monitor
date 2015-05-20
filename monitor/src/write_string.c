#include "write_string.h"

const int long_size = sizeof(long);
void write_string(pid_t child, long addr,char *str, int len)
{
    char *laddr;
    union u 
    {
        long val;
        char chars[long_size];
    }data;
    int i = 0;
    int j = len / long_size;
    int k = len % long_size;
    laddr = str;
    while(i < j) 
    {
        memcpy(data.chars, laddr, long_size);
        ptrace(PTRACE_POKEDATA, child,addr + i * long_size, data.val);
        ++i;
        laddr += long_size;
    }  
    if(k != 0) 
    {
        memset(data.chars,0,long_size);
        memcpy(data.chars, laddr, k);
        ptrace(PTRACE_POKEDATA, child,addr + j * long_size, data.val);
    }
    return;
}