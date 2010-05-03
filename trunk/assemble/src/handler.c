#include "../include/handler.h"
#include <stdio.h>
#include <pthread.h>

/*
void Matrix_Multiply(Processeur* Coproc_n)
 {
	 
	 
 }
 
 void Do_Nothing(Processeur *Coproc_n)
 {
	 
	 
 }
*/

void * Handler(void * p_Systolic)
{
	/* Lecture de fichier */
	t_Handler * Systolic = (t_Handler*) p_Systolic;
	char * salut = (char*)malloc(sizeof(long));
	//~ int error;
	//~ int i=0;
	
	pthread_mutex_lock(&(Systolic->mutex_depart_handler));
	pthread_cond_wait(&(Systolic->depart_handler), &(Systolic->mutex_depart_handler));
	printf("salut:\n");
	scanf("%c",salut);

	pthread_barrier_wait(&(Systolic->barrier));
	
	pthread_mutex_unlock(&(Systolic->mutex_depart_handler));
	free(salut);
	pthread_exit(NULL);
}

/* EOF*/

