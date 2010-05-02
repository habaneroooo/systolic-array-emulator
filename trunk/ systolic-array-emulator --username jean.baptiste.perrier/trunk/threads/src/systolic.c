#include "../include/systolic.h"

int main(int argc, char *argv[])
{
	int vIndex_x, vIndex_y;
	int vTestCreateNOK,vTestCreatNOK2;	
	t_Args * MyArgs;
	t_Handler Systolic;
	Systolic.ThreadArray = (pthread_t*)malloc(sizeof(pthread_t)*ROW_SIZE*ROW_SIZE);
	Systolic.ArgsArray = (t_Args*)malloc(sizeof(t_Args)*ROW_SIZE*ROW_SIZE);
	Systolic.Handler = (pthread_t*)malloc(sizeof(pthread_t));
	
	/* Synchronization mutex */
	vTestCreateNOK = pthread_cond_init(&Systolic.depart_handler, NULL);
	vTestCreatNOK2 = pthread_mutex_init(&Systolic.mutex_depart_handler,NULL);
	if(vTestCreateNOK)
	{
		printf("Error initialiazing Mutexes: %d\n", vTestCreateNOK);
		exit(-1);
	}
	
	/* Creates the GTK interface, and waits for start order */
	
	/* Checks data */
	
	/* Handler creation */
	
	vTestCreateNOK = pthread_barrier_init(&(Systolic.barrier), NULL, ROW_SIZE*ROW_SIZE+1);
	if(vTestCreateNOK)
	{
		printf("ERROR; return code from pthread_barrier_init() is %d\n",vTestCreateNOK);
		return(-1);
	}
	
	vTestCreateNOK = pthread_create(Systolic.Handler, NULL, Handler, (void *) &Systolic);
	
	/*Tests if the thread was correctly created */
	if(vTestCreateNOK)
	{
		printf("ERROR; return code from pthread_create() is %d\n",vTestCreateNOK);
		return(-1);
	}

	/* Threads creation */
	for(vIndex_x = 0;vIndex_x < ROW_SIZE; vIndex_x++)
	{
		for(vIndex_y = 0;vIndex_y < ROW_SIZE; vIndex_y++)
		{
			MyArgs = (Systolic.ArgsArray+vIndex_x*ROW_SIZE+vIndex_y);
			MyArgs->threadID = (vIndex_x*ROW_SIZE)+(vIndex_y+1);
			MyArgs->barrier = &(Systolic.barrier);
			
			/* Creates the thread */
			vTestCreateNOK = pthread_create(Systolic.ThreadArray+ROW_SIZE*vIndex_x + vIndex_y, NULL, CoProcessor_n, (void *) MyArgs);
			/*Tests if the thread was correctly created */
			if(vTestCreateNOK)
			{
				printf("ERROR; return code from pthread_create() is %d\n",vTestCreateNOK);
				return(-1);
			}
		}
	}
	
	/* Starts the handler, gives it the program to run */
	pthread_cond_signal(&Systolic.depart_handler);
	/* Prints out the result on the GTK window */
	
	pthread_exit(NULL);
	free((void*)&Systolic);
	(void)argc;
	(void)argv;
}


//~ void Handler0
//~ {	
	//~ int Index_exec;
	
	//~ /* Partie Execution de tous les co-processeurs */
	//~ /* En réalité, cette partie est effectuée en parallèle */
	//~ for(Index_exec=0; Index_exec < NB_PROC; Index_exec++)
	//~ {
		//~ /* On peut remplacer l'appel de fonction par le contenu de la fonction pointée, */
		//~ /* mais la synthaxe est plus explicite en appelant cette fonction */
		//~ Execute(*Array,Index_exec, In
	//~ }
//~ }
