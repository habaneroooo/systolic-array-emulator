#ifndef __COPROC__
#define COPROC

//extern typedef struct t_Args;
extern pthread_cond_t synchro, depart_handler;

void *CoProcessor_n(void *);

#endif /* EOF */
