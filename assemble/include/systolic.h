#ifndef __SYSTOLIC__
#define __SYSTOLIC__

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "handler.h"

#define NB_INSTRUCTIONS 2
#define ROW_SIZE 4
#define NB_DIAGONALS (2*ROW_SIZE)-1
#define INSTRUCTION 1

#define NB_PROCS ROW_SIZE*ROW_SIZE

#define NB_REG 32
#define NB_STATIC_REG 6

void * CoProcessor_n(void *);

typedef struct
{
	int threadID;
	int reg[NB_REG+NB_STATIC_REG];
	int reg_out;
	int *reg_in;
	int nb_reg_in;	
	pthread_barrier_t * barrier;
}__attribute__((aligned(sizeof (int)))) t_Args;

typedef struct
{
	pthread_t * Handler;
	pthread_t * ThreadArray;
	t_Args * ArgsArray;
	pthread_barrier_t barrier;
	pthread_cond_t depart_handler; 
	pthread_mutex_t mutex_depart_handler;
}t_Handler;

#endif 

/* EOF */

