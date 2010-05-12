#ifndef __PARSER__
#define __PARSER__

 /*
  *
  */
#define TTRUE 1
#define FFALSE 0

#define STRMAXSIZE 100
#define MAX_NB_PROCESS_IFNDEF 42
#define MAX_NB_INSTRUCTIONS 42
#define BUFFERSIZE 12
#define MAXMACROLENGTH 12
#define FREE_AND_EXIT_VERIFY_PROCESS {	free(Process);	free(Instruction);	free(Buffer3);	return vIsProperlyDeclared;	}

#define NBINSTRUCTIONS 9

#define TOKEN_BEGIN_PROCESS "<"
#define TOKEN_END_PROCESS ">;"
#define TOKEN_END_CALCULATION "end"

#define NB_REG 32
#define NB_STATIC_REG 6

#define NB_MAX_PROCESS 10

/*
 * Function prototypes
 */
unsigned int fVerifyProcessSelector(t_MainWindow* ,t_calculation * ,char **,unsigned int,bool**);
int fVerifyProcessDeclaration(t_MainWindow *,t_tools *,char *, unsigned int, t_calculation*);
int fTestRegisterValidity(char**, t_process*,int,unsigned int*);
int fLinkTokenToFunc(char,t_list*,t_tools*);
int fgetline(FILE*, unsigned int*,char**);

#endif

/* EOF */
