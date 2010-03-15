#include "../include/script.h"

int main(int argc, char *argv[])
{
	FILE * p_file = NULL;
	char * p_string = NULL;
	int vTest = 1;
	int vIndex;
	int vNbcalculations = 0;
	char script[][STRMAXSIZE]={"#calculation","#process","#register","#end"};
	enum t_whereami fgsfds = begin;
	p_file = fopen("calculate","r");
	if(p_file == NULL)
	{
		printf("Error opening file\n");
		exit(-1);
	}
	else
	{
		p_string = (char *)gimmegimmegimme(sizeof(char),STRMAXSIZE,1);
		if(p_string == NULL)
		{
			printf("Out of memory\n");
			exit(-1);
		}
		else
		{
			do
			{
				fscanf(p_file,"%s",p_string);
			}while(*p_string != '#');
			
			/* Permet de trouver la macro que l'on a lu. */
			/* Puisqu'apres on se sert de fonctions, ce test trouve toujours la premiere macro du fichier. */ 
			
			/* TRADUIRE */
			
			for(vIndex = 0;(vIndex < NB_MACRO) &&  (vTest != 0 );vIndex++)
			{
				vTest = strcmp(p_string,&script[vIndex][0]);
			}
			if(vTest == 0)	
			{
				switch(vIndex)
				{
					case begin:			break;
					
					case calculation:		fgsfds = calculation;
										fCalculation(&fgsfds,p_file,vNbcalculations,(char*)script);
										vNbcalculations++;
										break;
					
					case after_calculation:	break;
					
					case register_ :		if(fgsfds == begin)
										{
											
										}
					
					default:				printf("Macro \"%s\" undefined\nIgnoring\n",p_string);
				}
			}
			else
			{
				printf("Not found\n");
			}
		}
		
		/* Clear dynamically declared memory space */
		free(p_string);
		
	} /* end check opening file */
	
	
	
	/* Masks unused variables */
	(void)argc;
	(void)argv;
}

void * gimmegimmegimme(int taille_data, int taille_x,int taille_y)
{
	void* p_data = (void *)malloc(taille_data*taille_x*taille_y);
	return (void*) p_data;
}

void fCalculation(void* fgsfds, FILE * p_file, int vNbcalculations, char * script)
{
	char * p_string = (char*)malloc(sizeof(char)*STRMAXSIZE);
	t_calculation sCalculation;
	int vIndex, vLengthRead;
	int vTest = 1;
	
	/* Scans the opened file for the calculation name */
	vLengthRead = fscanf(p_file,"%s",p_string);
	
	/* Verifies the calculation does have a name... */
	if(p_string == NULL)
	{
		printf("Error: #calculation with no name");
		exit(-1);
	}
	
	/* Checks the calculation's name's integrity*/
	if(!(strncmp(p_string,"#",1)))
	{
		printf("The name of a #calculation must NOT start with macro declaration caracter \"#\"!\n");
		exit(-1);
	}
	
	/* Gets the name defined in the script file */
	sCalculation.name = (char*)gimmegimmegimme(sizeof(char),vLengthRead,1);
	*(sCalculation.name) = *p_string;
	
	/* Gives the calculation a number */
	sCalculation.index = vNbcalculations;
	
	/* Initializes the instructions index */
	sCalculation.nbprocesses = (int)fscanf(p_file,"%c",p_string);
	sCalculation.lsprocess = (t_process*)gimmegimmegimme(sizeof(t_process),sCalculation.nbprocesses,1);
	for(vIndex=0;vIndex<sCalculation.nbprocesses;vIndex++)
	{
		sCalculation.lsprocess->index = vIndex;
		sCalculation.lsprocess->nbinstructions = 1;
		sCalculation.lsprocess->p_instructions = fvoid;
	}
	/* Scan for instructions */
	do
	{
		/* Searches for macros */
		do
		{
			vLengthRead = fscanf(p_file,"%s",p_string);
		}while(!strncmp(p_string,"#",1));
		
		/* Checks if it is a known macro */
		for(vIndex = 0;(vIndex < NB_MACRO) &&  (vTest != 0 );vIndex++)
		{
			vTest = strcmp(p_string,(script+vIndex*STRMAXSIZE+0));
		}
		
		/* Checks if the macro is a process declaration"*/
		/* vIndex == 1 is script[1][0] */
		if((vTest == 0) && (vIndex = 1))	
		{
			
		}
		
	//~ vLengthRead = fscanf(p_file,"%s",p_string);
	printf("%s\n",p_string);
	}while(!strcmp(p_string,"#end") || !(vLengthRead < 0) );
			
	/* Masks unused variables */
	(t_whereami*) fgsfds;
	
	/* free reserved memory */
	free(p_string);
}

/* EOF */
