#include "../include/script.h"

int main(int argc, char *argv[])
{
	FILE * p_file = NULL;
	char * p_string = NULL;
	int vMaxStringSize = STRMAXSIZE;
	int vTest = 1;
	int vIndex;
	int vNbcalculations = 0;
	char script[][STRMAXSIZE]={"#calculation","#process","#register","#end"};

	enum t_whereami fgsfds = begin;
	p_file = fopen("calculate","rb");
	if(p_file == NULL)
	{
		printf("Error opening file\n");
		exit(-1);
	}
	else
	{
		p_string = (char *)gimmegimmegimme(sizeof(char),vMaxStringSize,1);
		if(p_string == NULL)
		{
			printf("Out of memory\n");
			exit(-1);
		}
		else
		{
			printf("%s\n--\n",p_string);
			fgetline(p_file,&vMaxStringSize,&p_string);
			printf("%s\n--\n",p_string);

			free(p_string);
			exit(0);

			fgets(p_string,STRMAXSIZE,p_file);
			printf("%s\n",p_string);
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

	return 0;
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
	int vIndex, vLengthRead, nbInstructionsDeclared = 0;
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
	
	/* Initializes all processes */
	for(vIndex=0;vIndex<sCalculation.nbprocesses;vIndex++)
	{
		sCalculation.lsprocess->index = vIndex;
		sCalculation.lsprocess->nbinstructions = 1;
		(*(sCalculation.lsprocess)).p_instructions = (void(**)())malloc(sizeof(t_func*));
		*(*(sCalculation.lsprocess)).p_instructions = &fvoid;
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
			vLengthRead = fscanf(p_file,"%s",p_string);
			
			/* Checks if the next string is a macor (which is erroneous) */
			if(!strncmp(p_string,"#",1))
				
			/* If there is more than one instruction */
			if((vLengthRead > 1))
			{
				t_list vTemp;
				/* If the user grouped the instructions within brackets, it is taken into account */
				if(!strncmp(p_string,"{",1))
				{
					for(vIndex=0;(vIndex<vLengthRead)&&(strncmp(p_string,"}",1));vIndex++)
					{
						if(!fLinkCharToFunc(*p_string+vIndex,&vTemp))
						{
							
							nbInstructionsDeclared++;
							
							//~ (*(sCalculation.lsprocess)).p_instructions
							(*(sCalculation.lsprocess)).p_instructions = (void(**)())realloc((*(sCalculation.lsprocess)).p_instructions,(nbInstructionsDeclared*sizeof(void(*)())));
							if(sCalculation.lsprocess->p_instructions == NULL)
							{
								printf("Out of memory\n");
								exit(-1);
							}
							
							*((*(sCalculation.lsprocess)).p_instructions+nbInstructionsDeclared) = vTemp.func;
						}
					}
					sCalculation.lsprocess->nbinstructions = nbInstructionsDeclared;
				}
				else
				{
					vTest = 1;
					for(vIndex=0;(vIndex<vLengthRead)&&(vTest == 1);vIndex++)
					{
						vTest = fLinkCharToFunc(*(p_string+vIndex),&vTemp);
					}
					
				}
			}
		}
		/* else: other macro -> ignored */
		
	//~ vLengthRead = fscanf(p_file,"%s",p_string);
	printf("%s\n",p_string);
	}while(!strcmp(p_string,"#end") || !(vLengthRead < 0) );
			
	/* Masks unused variables */
	//~ (t_whereami*) fgsfds;
	
	/* free reserved memory */
	free(p_string);
}

int fLinkCharToFunc(char carac,t_list* sFuncToLink)
{
	int vIndex, vTest = 0;
	const t_list tab_list[NBINSTRUCTIONS] = {
		{'<',	fvoid},
		{'>',	fvoid},
		{'*',		fvoid},
		{'+',	fvoid}, 
		{'-',		fvoid},
		{'/',		fvoid},
		{'ø',		fvoid},
		{'%',	fvoid},
		{'&',	fvoid},
		{'|',		fvoid}
	};
	
	/* Finds the function linked to the character given */
	for(vIndex = 0; vIndex < NBINSTRUCTIONS; vIndex++)
	{
		if(tab_list[vIndex].carac == carac)
		{
			sFuncToLink->func = tab_list[vIndex].func;
			vTest = 1;
		}
	}

	return vTest;
}

int fgetline(FILE* p_file, int* n,char**p_string)
{
	int new_n = 0,stringlen;
	char c = 'o';
	stringlen = strlen(*p_string);
	while((c != '\x0A') && !feof(p_file))
	{
		printf("%d--%d--%c\x0A",strcmp(&c,"\x0A"),feof(p_file),c);
		if(new_n == *n)
		{
			stringlen *= 2;
			p_string = realloc(p_string,stringlen);
			if(p_string ==NULL)
			{
				printf("Out of memory\n");
				exit(-1);
			}
		}
		c = (char)fgetc(p_file);
		*(*p_string + new_n) = (char)c;
		new_n++;
	}
	printf("\n");
	if(new_n > *n)
	{
		*n = strlen(*p_string);
		realloc(p_string,*n);
	}
	return 0;
}

/* EOF */
