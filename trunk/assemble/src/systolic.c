#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/types.h"
#include "../include/parser.h"
#include "../include/systolic.h"
#include "../include/instructions.h"
#include "../include/gettext.h"

void fCreateThreads(t_toolbox* sToolbox, gint vActiveCalculation)
{
	gint vIndex;
	gint vTestCreateNOK;

	gint rowsize = (sToolbox->CalculationList+vActiveCalculation)->rowsize;

	sToolbox->systolic_array.ThreadArray = (pthread_t*)malloc(sizeof(pthread_t)*rowsize*rowsize);
	sToolbox->systolic_array.ArgsArray = (t_Args*)malloc(sizeof(t_Args)*rowsize*rowsize);
	sToolbox->systolic_array.Handler = (pthread_t*)malloc(sizeof(pthread_t));
	

	/* Synchronization mutex */
	vTestCreateNOK = pthread_cond_init(&sToolbox->systolic_array.depart_handler, NULL);
	if(vTestCreateNOK)
	{
		g_printf(_("Error initializing mutexes: %d\n"), vTestCreateNOK);
		exit(-1);
	}

	vTestCreateNOK = pthread_mutex_init(&sToolbox->systolic_array.mutex_depart_handler,NULL);
	if(vTestCreateNOK)
	{
		g_printf(_("Error initializing synchronization of handler: %d\n"), vTestCreateNOK);
		exit(-1);
	}
	
	/* Handler creation */
	vTestCreateNOK = pthread_barrier_init(&(sToolbox->systolic_array.barrier), NULL, rowsize*rowsize+1);
	if(vTestCreateNOK)
	{
		g_printf(_("ERROR; return code from pthread_barrier_init() is %d\n"),vTestCreateNOK);
		exit(-1);
	}
	
	vTestCreateNOK = pthread_create(sToolbox->systolic_array.Handler, NULL, Handler, static_cast<gpointer>(sToolbox));
	if(vTestCreateNOK)
	{
		g_printf(_("ERROR; return code from pthread_create() is %d\n"),vTestCreateNOK);
		exit(-1);
	}

	/* Threads creation */
	for(vIndex = 0;vIndex < rowsize*rowsize; vIndex++)
	{
		t_Args * MyArgs = (sToolbox->systolic_array.ArgsArray+vIndex);
		MyArgs->threadID = (vIndex+1);
		MyArgs->quit = FALSE;
		MyArgs->barrier = &(sToolbox->systolic_array.barrier);
		MyArgs->func = fvoid;

		/* Creates the thread */
		vTestCreateNOK = pthread_create(sToolbox->systolic_array.ThreadArray+vIndex, NULL, CoProcessor_n, static_cast<gpointer>(MyArgs));
		/*Tests if the thread was correctly created */
		if(vTestCreateNOK)
		{
			g_printf(_("ERROR; return code from pthread_create() is %d\n"),vTestCreateNOK);
			exit(-1);
		}
	}

//	pthread_exit(NULL);
}


void* CoProcessor_n(gpointer user_data)
{
	t_Args sArgs = *(static_cast<t_Args*>(user_data));
//	g_printf("debug\n");
	while(1)
	{
		pthread_barrier_wait(POINTER_TO_ARGS->barrier);
		if(POINTER_TO_ARGS->quit == TRUE)
			break;
		else
			(*(POINTER_TO_ARGS->func))(&(POINTER_TO_ARGS->reg_out),POINTER_TO_ARGS->reg_in,POINTER_TO_ARGS->nb_reg_in);

		pthread_barrier_wait(POINTER_TO_ARGS->barrier);
	}
//	g_printf("My args:\nThreadID: %d\n\n", sArgs.threadID);
	pthread_exit(NULL);
}

void * Handler(gpointer user_data)
{
	/* Local variables */
	gint vIndex_x = 0, vIndex_y = 0,vIndex_func = 0;
	/* Copies everything locally so it executes faster */
	gint chosen_calculation = gtk_combo_box_get_active(GTK_COMBO_BOX(static_cast<t_toolbox*>(user_data)->WindowList.main.combobox));
	t_Handler * Systolic = &(static_cast<t_toolbox*>(user_data)->systolic_array);
	t_calculation sCalculation = *(static_cast<t_toolbox*>(user_data)->CalculationList+chosen_calculation);
	gint cycle_n = 2;
	gint rowsize = sCalculation.rowsize;
	gint nbprocesses = sCalculation.nbprocesses;

	pthread_mutex_lock(&(Systolic->mutex_depart_handler));

//	for(cycle_n = 0; cycle_n < rowsize*rowsize;cycle_n++)
//	{
//		for(vIndex_func = 0; vIndex_func < sCalculation.nbprocesses;vIndex_func++)
//		{
			/* function assignements */
			for(vIndex_x = 0; vIndex_x < rowsize;vIndex_x++)
			{
				for(vIndex_y = 0; vIndex_y < rowsize;vIndex_y++)
				{
					if((cycle_n >= vIndex_y+vIndex_x) && (cycle_n < vIndex_x+vIndex_y+(nbprocesses-1)))
		//			if((cycle_n == vIndex_y+vIndex_x))
					{
//						if(*((sCalculation.lsprocess+vIndex_func)->hmask+(vIndex_y+vIndex_y)) && *((sCalculation.lsprocess+vIndex_func)->vmask+(vIndex_y+vIndex_y)))
						if(*(sCalculation.lsprocess->hmask+(vIndex_y+vIndex_y)) && *(sCalculation.lsprocess->vmask+(vIndex_y+vIndex_y)))
						{
							t_Args * p_args = Systolic->ArgsArray+(vIndex_x*rowsize+vIndex_y);
//							p_args->func = (sCalculation.lsprocess+vIndex_func)->p_instructions;
							g_printf("%d ff\n",p_args->threadID);
							p_args->func = sCalculation.lsprocess->p_instructions;
							g_printf("oui:%d\n",(vIndex_x*rowsize+vIndex_y));
						}
						else
						{
							t_Args * p_args = Systolic->ArgsArray+(vIndex_x*rowsize+vIndex_y);
							p_args->func = fvoid;
							g_printf("non:%d\n",(vIndex_x*rowsize+vIndex_y));
						}
					}
				}
			}
//		}
//	}
	pthread_cond_wait(&(Systolic->depart_handler), &(Systolic->mutex_depart_handler));

	/* Start */
	pthread_barrier_wait(&(Systolic->barrier));
	/* Wait for every thread to finish */
	pthread_barrier_wait(&(Systolic->barrier));

#if SHOW_REGISTERS_IN_RESULT_WINDOW == TRUE
	/* Prints out the results */
	gdk_threads_enter();
	for(vIndex_x = 0; vIndex_x < rowsize;vIndex_x++)
	{
		for(vIndex_y = 0; vIndex_y < rowsize;vIndex_y++)
		{
			t_Args * p_args = Systolic->ArgsArray+(vIndex_x*rowsize+vIndex_y);
			GtkWidget * p_entry = *(static_cast<t_toolbox*>(user_data)->WindowList.result.entry+(vIndex_x*rowsize+vIndex_y));
			gtk_entry_set_text(GTK_ENTRY(p_entry),(gchar*)g_strdup_printf("%d",p_args->reg_out));
		}
	}
	gdk_threads_leave();
#endif

	for(vIndex_x = 0; vIndex_x < rowsize;vIndex_x++)
	{
		for(vIndex_y = 0; vIndex_y < rowsize;vIndex_y++)
		{
			t_Args * p_args = Systolic->ArgsArray+(vIndex_x*rowsize+vIndex_y);
			p_args->quit = TRUE;
		}
	}

	pthread_barrier_wait(&(Systolic->barrier));
	pthread_barrier_wait(&(Systolic->barrier));
	//	free(sToolbox->systolic_array.ThreadArray);
	//	free(sToolbox->systolic_array.ArgsArray);
	//	free(sToolbox->systolic_array.Handler);

	pthread_mutex_unlock(&(Systolic->mutex_depart_handler));
	pthread_exit(NULL);
}

/* EOF */

