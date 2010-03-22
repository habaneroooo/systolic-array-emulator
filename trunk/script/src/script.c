#include "../include/script.h"

int main(int argc, char *argv[])
{
	FILE * p_file;
	char * p_string = NULL;
	int vMaxStringSize = STRMAXSIZE;
	int vTest = 1;
	int vIndex;
	int vNbcalculations = 0;
	char script[][STRMAXSIZE]={"#calculation","#process","#register","#end"};

	t_whereami fgsfds = begin;
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
			/* This test always finds the first macro in the script file */
			do
			{
				fgetline(p_file,&vMaxStringSize,&p_string);
			}while(*p_string != '#');
			printf("%s",p_string);
			/* Permet de trouver la macro que l'on a lu. */
			for(vIndex = 0;(vIndex < NB_MACRO) &&  (vTest != 0 );vIndex++)
			{
				vTest = strcmp(p_string,&script[vIndex][0]);
				printf("%d\n",vTest);
			}
			if(vTest == 0)	
			{
				switch(vIndex)
				{
					case begin:				break;
					
					case calculation:		fgsfds = calculation;
											fCalculation(&fgsfds,p_file,vNbcalculations,(char*)script,p_string,&vMaxStringSize);
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
/*
 * fCalculation():
 * Scans trough the script file for processes and allocates memory according to what's written inside that file
 *
 * Arguments:
 * (void*)	fgsfds:
 * (FILE*)	p_file: the script file
 * (int)	vNbcalculations:
 * (char*)	script: A list of the known macros.
 * (char*)	p_string: General string used to read through the script file
 * (int*)	p_vMaxStringSize: the current length of p_string
 */
void fCalculation(void* fgsfds, FILE * p_file, int vNbcalculations, char * script, char* p_string, int* p_vMaxStringSize)
{
	/* The calculation we're about to read */
	t_calculation sCalculation;

	/* General index variable (useful in for(;;)'s)*/
	int vIndex;

	/* Used to verify the number of character read in standart string.h functions. */
	int vLengthRead;

	/* */
	int nbInstructionsDeclared = 0;

	/* General test variable */
	int vTest = 1;
	
	/* Scans the opened file for the calculation name */
	vLengthRead = sscanf(p_string,"%*s %s %d",sCalculation.name,&nbInstructionsDeclared);
	
	/* Verifies the calculation does have a name... */
	if(vLengthRead == 1)
	{
		sprintf(sCalculation.name,"%c",(char)vNbcalculations+1+'0');
		printf("Error: #calculation with no name\nRenamed \"%s\"",sCalculation.name);
		//exit(-1);
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
		(*(sCalculation.lsprocess)).p_instructions = (void(**)())malloc(sizeof(void(**)()));
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
							
							*((*(sCalculation.lsprocess)).p_instructions+nbInstructionsDeclared) = vTemp.instructions->func;
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
			
			vLengthRead = fscanf(p_file,"%d",&vTest);
			if(vLengthRead > 1)
			{
				for(vIndex = 1;(vIndex <vTest)&&(vIndex < sCalculation.nbprocesses);vIndex++)
				{
					*(sCalculation.lsprocess+vIndex)= *(sCalculation.lsprocess);
				}
			}
		}
		/* else: other macro -> ignored */
		
	//~ vLengthRead = fscanf(p_file,"%s",p_string);
	printf("%s\n",p_string);
	}while(!strcmp(p_string,"#end") || !(vLengthRead < 0) );
			
	/* Masks unused variables */
	(t_whereami*) fgsfds;
	
	/* free reserved memory */
	free(p_string);
	free((void*)sCalculation.lsprocess);
}

int fLinkCharToFunc(char carac,t_list* sFuncToLink)
{
	int vIndex, vTest = 0;

	/*
	 * We could reduce the size of this table, however the purpose of having a big table here is
	 * that we don't have to check the type of the datas when executing the program
	 */
	

	/* Finds the function linked to the character given */
	for(vIndex = 0; vIndex < NBINSTRUCTIONS; vIndex++)
	{
		if(tab_list[vIndex].carac == carac)
		{
			sFuncToLink->instructions->func = tab_list[vIndex].instructions->func;
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
		if(new_n == *n)
		{
			stringlen *= 2;
			p_string = (char**)realloc(p_string,stringlen);
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
	if(new_n > *n)
	{
		*n = strlen(*p_string);
		p_string = (char**)realloc(p_string,stringlen);
	}
	return 0;
}

/* EOF */
