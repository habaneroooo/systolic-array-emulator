#ifndef __SYSTOLIC__
#define __SYSTOLIC__

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/instructions.h"

#define NB_MACRO 2
#define NBINSTRUCTIONS 11
#define STRMAXSIZE 100

typedef enum t_whereami {begin,calculation,after_calculation,register_};

typedef struct {
	char * name;
	int index;
	int nbinstructions;
	void (*(*p_instructions))();
}t_process;

typedef struct {
	char * name;
	int index;
	int nbprocesses;
	t_process * lsprocess;
}t_calculation;

typedef struct {
	char carac;
	void (*func)();
}t_list;

void fCalculation(void*, FILE*,int,char*);
void * gimmegimmegimme(int , int ,int );
int fLinkCharToFunc(char,t_list*);

#endif /* EOF */
