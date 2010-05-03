#ifndef __SYSTOLIC__
#define __SYSTOLIC__

#include "link.h"
#include "parser.h"

int fParseFile(FILE *);
int fGetCalculation(t_whereami*, FILE *, int , t_tools*);
void fProcess(FILE *, t_tools *, t_calculation *,unsigned int *);
void fParseCalculation(FILE *,t_tools *, t_calculation*);

#endif 

/* EOF */
