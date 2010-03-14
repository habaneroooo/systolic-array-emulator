#ifndef __SYSTOLIC__
#define __SYSTOLIC__

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/instructions.h"

#define NB_MACRO 2

typedef enum whereami {begin,calculation,register_};

void fCalculation(void*, FILE*, char*);
void * gimmegimmegimme(int , int ,int );

#endif /* EOF */
