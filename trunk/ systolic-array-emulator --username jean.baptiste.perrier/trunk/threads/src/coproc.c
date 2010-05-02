#include <stdio.h>
#include <pthread.h>
#include "../include/coproc.h"
#include "../include/systolic.h"

void* CoProcessor_n(void * CoProcArgs)
{
	t_Args * psArgs = (t_Args*) CoProcArgs;
	int error;	
	pthread_barrier_wait(psArgs->barrier);
	printf("My args:\nThreadID: %d\n\n", psArgs->threadID);
	pthread_exit(NULL);
}

