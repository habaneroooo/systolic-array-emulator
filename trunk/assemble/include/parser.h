#ifndef __PARSER__
#define __PARSER__

/*
 * STANDARD LIBRARIES ONLY
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

 /*
  *
  */
#define TTRUE 1
#define FFALSE 0

#define NB_MACRO 3
#define STRMAXSIZE 100
#define MAX_NB_PROCESS_IFNDEF 42
#define MAX_NB_INSTRUCTIONS 42
#define BUFFERSIZE 12
#define MAXMACROLENGTH 12
#define FREE_AND_EXIT_VERIFY_PROCESS {	free(Process);	free(Instruction);	free(Buffer3);	return vIsProperlyDeclared;	}

#define NBINSTRUCTIONS 9

#define MAX_REGISTER_TOKEN_LENGTH 4
#define MAX_INSTRUCTION_TOKEN_LENGTH 3
#define TOKEN_BEGIN_PROCESS "<"
#define TOKEN_END_PROCESS ">;"
#define TOKEN_END_CALCULATION "end"

#define NB_REG 32
#define NB_STATIC_REG 6
/* Specific types declaration */
typedef enum {begin,calculation,after_calculation,register_,process} t_whereami;

typedef void (*t_func)(void);

typedef struct {
	bool * hmask;
	bool * vmask;
	int reg_out;
	int * reg_in;
	int nb_reg_in;
	t_func p_instructions;
}t_process;

typedef struct {
	char * name;
	unsigned int index;
	unsigned int rowsize;
	unsigned int nbprocesses;
	t_process * lsprocess;
}t_calculation;

typedef struct {
	t_whereami context;
	long line;
	char* Buffer;
	unsigned int MaxStringSize;
	char* MacroList[NB_MACRO];
	unsigned int MaxMacroLength;
	char * String;
	long CurrentStringSize;
}t_tools;

typedef struct
{
	char reg[MAX_REGISTER_TOKEN_LENGTH];
	int num;
}t_reg;

typedef struct {
	char carac[MAX_INSTRUCTION_TOKEN_LENGTH+1];
	void (*func)();
	unsigned char NbMinDataIn;
	unsigned char NbMaxDataIn;
}t_list;

/*
 * Function prototypes
 */
unsigned int fVerifyProcessSelector(t_calculation * ,char **,unsigned int,bool**);
int fVerifyProcessDeclaration(t_tools *,char *, unsigned int, t_calculation*);
int fTestRegisterValidity(char**, t_process*,int,unsigned int*);
int fLinkTokenToFunc(char,t_list*,t_tools*);
int fgetline(FILE*, unsigned int*,char**,long*);

/*
 * Other libraries
 */
#include "script.h"
#include "instructions.h"

/*
 * Global variables declaration go here
 * Try not to declare too many - use pointers instead.
 */
const t_list tab_list[NBINSTRUCTIONS] = 
{
		{"+",fvoid,2,0xFF},
		{"*",fvoid,2,0xFF},
		{"-",fvoid,2,100},
		{"/",fvoid,2,0xFF},
		{"ø",fvoid,2,0xFF},
		{"%",fvoid,2,0xFF},
		{"&",fvoid,2,0xFF},
		{"|",fvoid,2,0xFF},
		{"set",fvoid,3,0xFF}
};

const t_reg Registers[NB_STATIC_REG] =
{
	{"C",NB_REG+0},
	{"CW",NB_REG+1},
	{"CN",NB_REG+2},
	{"CE",NB_REG+3},
	{"CS",NB_REG+4},
	{"REG",0}
};

#endif

/* EOF */
