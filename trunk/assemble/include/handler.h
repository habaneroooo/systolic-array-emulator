#ifndef __HANDLER__
#define __HANDLER__

#include "systolic.h"

void * Handler(void*);

extern pthread_cond_t synchro, depart_handler;

#endif /* EOF */
