#ifndef __SYSTOLIC__
#define __SYSTOLIC__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//~ #include <iostream>
//~ #include <ifstream>
#include "../include/instructions.h"
//~ using namespace std;

#define NB_MACRO 2
#define NBINSTRUCTIONS 11
#define STRMAXSIZE 100

typedef enum t_whereami {begin,calculation,after_calculation,register_};
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

typedef struct {
	char carac;
	void (*func)();
}t_list;

void fCalculation(void*, FILE*,int,char*);
void * gimmegimmegimme(int , int ,int );
int fLinkCharToFunc(char,t_list*);
int fgetline(FILE*, int*,char**);

#endif 

/* EOF */
