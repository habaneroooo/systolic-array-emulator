#ifndef __SYSTOLIC__
#define __SYSTOLIC__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/link.h"

#define NB_MACRO 4
#define STRMAXSIZE 100

typedef enum {begin,calculation,after_calculation,register_} t_whereami;
typedef void (*t_func)(void);

typedef struct {
	char * name;
	int index;
	int nbinstructions;
	t_func *p_instructions;
}t_process;

typedef struct {
	char * name;
	int index;
	int rowsize;
	int nbprocesses;
	t_process * lsprocess;
}t_calculation;

void fCalculation(void*, FILE*,int,char*,char*,int*);
void * gimmegimmegimme(int ,int ,int );
int fLinkCharToFunc(char,t_list*);
int fgetline(FILE*, int*,char**);

#endif 

/* EOF */
