#ifndef __SYSTOLIC_H_
#define __SYSTOLIC_H_

#define POINTER_TO_ARGS static_cast<t_Args*>(user_data)

void fCreateThreads(t_toolbox*, gint);
void *Handler(gpointer);
void *CoProcessor_n(gpointer);

extern pthread_cond_t synchro, depart_handler;


#endif 

/* EOF */

