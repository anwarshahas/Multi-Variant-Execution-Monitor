#include "termination.h"
#include "color.h"
void process_termination(int flag)
{
	printf("\n\n---------------------------------------------------------------\n\n");
	if(flag==1||flag==2)
    	printf("Process completed Normally::\nMonitor is shutting Down due to process completion\n");
	else
    	printf(ANSI_COLOR_RED  "Attack detected::Execution stopped\nMonitor is shutting Down due to attack detection\n" ANSI_COLOR_RESET);
    printf("*****************************************************************************\n");
}