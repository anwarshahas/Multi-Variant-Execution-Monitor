VPATH = src:src/system_calls
CC = gcc
CFLAGS = -w
objects = main.o read_string.o write_string.o init.o variants.o monitor_waiting.o miss_match.o reg_setting.o sys_call_check.o sys_calls_1_20.o sys_calls_exec_mode.o sys_calls_21_40.o debug.o black_list.o termination.o
OBJDIR := objdir
OBJS := $(addprefix $(OBJDIR)/,$(objects))
$(OBJDIR)/%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@
all: $(OBJS)
$(OBJS): | $(OBJDIR)
$(OBJDIR):
	mkdir $(OBJDIR)
install: $(objects)
	$(CC) $(CFLAGS) -o monitor $(objects)
	$(RM) *.o
clean:
	rm -rf objdir monitor
