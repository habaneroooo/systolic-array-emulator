#ifndef __SYSTOLIC__
#define __SYSTOLIC__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/link.h"

#define NB_MACRO 5
#define STRMAXSIZE 100
#define MAX_NB_PROCESS_IFNDEF 42
#define MAX_NB_INSTRUCTIONS 42
#define BUFFERSIZE 12
#define MAXMACROLENGTH 12

typedef enum {begin,calculation,after_calculation,register_} t_whereami;
typedef void (*t_func)(void);

typedef struct {
	int index;
	int nbinstructions;
	t_func *p_instructions;
}t_process;

typedef struct {
	char * name;
	unsigned int index;
	unsigned int rowsize;
	unsigned int nbprocesses;
	t_process * lsprocess;
}t_calculation;

typedef struct {
	char* Buffer;
	unsigned int MaxStringSize;
	char* MacroList[NB_MACRO];
	unsigned int MaxMacroLength;
	char * String;
}t_tools;

void fCalculation(void*, FILE *, int , t_tools*);
void fProcess(FILE *, t_tools *, t_calculation *,unsigned int *);
void * gimmegimmegimme(int , int ,int );

int fLinkCharToFunc(char,t_list*);
int fgetline(FILE*, unsigned int*,char**);
void InitMacroTable(t_tools *);
void fGetNBProcess(FILE *,t_tools *, unsigned int *);

#endif 

/* EOF */
