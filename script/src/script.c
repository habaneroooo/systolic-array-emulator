#include "../include/script.h"

int main(int argc, char *argv[])
{
	FILE * p_file = NULL;
	char * p_string = NULL;
	int vTest = 1;
	int vIndex;
	char script[NB_MACRO][128]={"#calculation"};
	enum whereami fgsfds = begin;
	p_file = fopen("calculate","r");
	if(p_file == NULL)
	{
		printf("Error opening file\n");
		exit(-1);
	}
	else
	{
		p_string = (char *)gimmegimmegimme(sizeof(char),128,1);
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
				vTest = strcmp(p_string,&script[0][0]);
			}
			if(vTest == 0)	
			{
				switch(vIndex)
				{
					case begin:		printf("no\n");
									break;
					
					case calculation:	printf("yes\n");
									fgsfds = calculation;
									break;
					
					default:	printf("other\n");
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

void fCalculation(whereami* fgsfds, FILE * p_file, char * p_string)
{
	realloc(); 
	do
	{
		fscanf(p_file,"%s",p_string);
	}while(strcmp(p_string,"#end") || (p_string == NULL));
	
	/* Masks unused variables */
	//~ (whereami*) fgsfds;
}

/* EOF */
