#ifndef __COPROC__
#define COPROC

extern pthread_cond_t synchro, depart_handler;

void *CoProcessor_n(void *);

#endif /* EOF */
