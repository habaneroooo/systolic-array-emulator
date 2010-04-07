#include "../include/script.h"

int main(int argc, char *argv[])
{
	FILE * p_file;
	unsigned int vTest = 1;
	int vIndex;
	int vLengthRead;
	int vNbcalculations = 0;
	char**bidon=NULL;
	t_tools Tools;
	t_whereami fgsfds = begin;

	char script[NB_MACRO][STRMAXSIZE]={"#calculation","#process","#row","#register","#end"};

	p_file = fopen("calculate","rb");
	if(p_file == NULL)
	{
		printf("Error opening file\n");
		exit(-1);
	}
	else
	{
		Tools.MaxMacroLength = MAXMACROLENGTH;
		Tools.MaxStringSize = STRMAXSIZE;
		Tools.Buffer = (char*)gimmegimmegimme(sizeof(char),1,Tools.MaxMacroLength+1);
		if(Tools.Buffer == NULL)
		{
			printf("Out of memory\n");
			//~ exit(-1);
		}
		for(vIndex=0;vIndex<NB_MACRO;vIndex++)
		{
			Tools.MacroList[vIndex] = (char*)gimmegimmegimme(sizeof(char),1,Tools.MaxMacroLength);
			if(Tools.MacroList[vIndex] == NULL)
			{
				printf("Out of memory\n");
				//~ exit(-1);
			}
		}
		for(vIndex=0;vIndex<NB_MACRO;vIndex++)
		{
			Tools.MacroList[vIndex] = script[vIndex];
		}
		Tools.String = (char*)gimmegimmegimme(sizeof(char),1,Tools.MaxStringSize);
		if(Tools.String == NULL)
		{
			printf("Out of memory\n");
			exit(-1);
		}
		else
		{
			/* This test always finds the first macro in the script file */
			do
			{
				fgetline(p_file,&Tools.MaxStringSize,&Tools.String);
			}while(*Tools.String != '#');
			vLengthRead = sscanf(Tools.String,"%s",Tools.Buffer);
			/* Permet de trouver la macro que l'on a lu. */
			for(vIndex = 0;(vIndex < NB_MACRO) &&  (vTest != 0 );vIndex++)
			{
				bidon =Tools.MacroList;
				vTest = strcmp(Tools.Buffer,Tools.MacroList[vIndex]);
				//~ printf("1--%s--%s\n",Tools.Buffer,Tools.MacroList[vIndex]);
			}
			if(vTest == 0)	
			{
				switch(vIndex)
				{
					case begin:			break;
					
					case calculation:		fgsfds = calculation;
										fCalculation(&fgsfds,p_file,vNbcalculations,&Tools);
										vNbcalculations++;
										break;
					
					case after_calculation:	break;
					
					case register_ :		if(fgsfds == begin)
										{

										}

					default:				/* This can only happen if you have not the same number of */
										/* macros declared and defined in NB_MACRO (script.h) */
										printf("Macro \"%s\" undefined\nIgnoring\n",Tools.String);
				}
			}
			else
			{
				printf("Not found\n");
			}
		}
		
		/* Clear dynamically declared memory space */
		
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
void fCalculation(void* fgsfds, FILE * p_file, int vNbcalculations, t_tools * p_Tools)
{
	/* The calculation we're about to read */
	//~ MAKE THIS A POINTER AND HAVE IT RETURN AN ERROR CODE
	t_calculation sCalculation;
	
	/* */
	unsigned int nbProcessDeclared = 0;
	unsigned int nbCorrectProcess = 0;
	
	/* General purpose index variable */
	//~ unsigned int vIndex;
	
	/* Used to verify the number of character read in standard string.h functions. */
	unsigned int vLengthRead;
	
	/* General purpose test variables */
	unsigned int vTest = 1;
	unsigned int vTest2 = 1;
	unsigned int vEnd = 1;
	
	/* Gets the name & number of processes */
	p_Tools->String++;
	
	/* Scans the opened file for the calculation name */
	//~ POSSIBILITE DE BUG SUR LA LONGUEUR
	sCalculation.name = (char*)gimmegimmegimme(sizeof(char),p_Tools->MaxStringSize,1);
	vLengthRead = sscanf(p_Tools->String,"%*s %s",sCalculation.name);
	
	/* Verifies the calculation does have a name... */
	if(vLengthRead == 0)
	{
		sCalculation.name = (char*)realloc(sCalculation.name,sizeof(char));
		sprintf(sCalculation.name,"%c",(char)vNbcalculations+1+'0');
		printf("Error: #calculation with no name\nRenamed \"%s\"\n",sCalculation.name);
		//~ exit(-1);
	}
	
	/* Initializes the instructions index */
	vTest2 = sscanf(p_Tools->String,"%*s %u",&sCalculation.nbprocesses);
		
	/* This test always finds the first macro in the calculation */
	/* Gets the matrix size */
	vTest=1;
	do
	{
		vLengthRead = fgetline(p_file,&p_Tools->MaxStringSize,&p_Tools->String);
		sscanf(p_Tools->String,"%4s",p_Tools->Buffer);
		vTest = strncmp(p_Tools->Buffer,"#row",1);
	}while(vTest && (vLengthRead > 0));
	//~ TESTER ICI SI ON A FINI LE FICHIER
	
	/* If we found a macro */
	if(!vTest)
	{
		if(!strcmp(p_Tools->Buffer,"#row"))
		{
			vLengthRead = sscanf(p_Tools->String,"%*s %u",&sCalculation.rowsize);
			
			/* "#row" was specified, but the size was not */
			if(!vLengthRead)
			{
				printf("Error: the matrix size for calculation %s was not specified\n",sCalculation.name);
				printf("Ignoring calculation.\n");
				//~ exit(-1);
			}
			else
			{
				
				/* Gets the number of process declared */
				/* WARNING: meaning of vTest switched to "reading errors" */
				fGetNBProcess(p_file,p_Tools,&nbProcessDeclared);
				
				/* Tests*/
				if(!nbProcessDeclared)
				{
					printf("Error: Empty calculation \"%s\"\nIgnoring calculation.\n",sCalculation.name);
					//~ exit(-1);
				}
				else
				{
					sCalculation.lsprocess = (t_process*)malloc(sizeof(t_process*));
				}
			}
		}
		else
		{
			printf("Error: the matrix size for calculation %s was not specified.\n",sCalculation.name);
			printf("Ignoring calculation.\n");
			//~ exit(-1);
		}
	}
	/* If no macro were found = empty calculation */
	else
	{
		printf("Error: Empty calculation \"%s\".\nIgnoring calculation.",sCalculation.name);
		//~ exit(-1);
	}
	/* Initializes all processes */
	/* there is 2*ROWSIZE-1+(NBINSTRUC-1) cycls in a ROWSIZE*ROWSIZE matrix for NBINSTRUC to be executed in diagonale */
	
	//~ *************************
	//~ SI on a lu une macro, ne pas relire
	//~ *************************
	
	/* Scan for instructions */
	do
	{
		/* re/initializes test variables */
		vEnd=1;
		vTest=1;
		
		/* Finds the first macro in the calculation */
		do
		{
			vLengthRead = fgetline(p_file,&p_Tools->MaxStringSize,&p_Tools->String);
			if(vLengthRead > 0)
			{
				/* '8' here is the number of characters in "#process" */
				sscanf(p_Tools->String,"%8s",p_Tools->Buffer);
				printf("%s\n",p_Tools->String);
				
				/* The other macros are ignored */
				vTest = strcmp(p_Tools->Buffer,"#process");
				vEnd = strcmp(p_Tools->Buffer,"#end") ;
			}
		}while(vTest && vEnd && (vLengthRead > 0));
		
		//~ *************************
		/* Check if we're at the end of the file */
		//~ *************************
		
		/* Checks if the previous loop found a macro and if it is a process declaration"*/
		if((vTest == 0) && !strncmp(p_Tools->String,"#process",8))
		{
			t_process * sProcess;
			nbCorrectProcess++;
			sCalculation.lsprocess = (t_process*)realloc(sCalculation.lsprocess,sizeof(t_process)*(nbCorrectProcess+1));
			sProcess  = sCalculation.lsprocess+nbCorrectProcess-1;
			sProcess->index = nbCorrectProcess;
			sProcess->nbinstructions = 1;
			sProcess->p_instructions = (void(**)())malloc(sizeof(void
			*(sProcess->p_instructions) = &fvoid;
			/* */
			fProcess(p_file,p_Tools,&sCalculation,&nbCorrectProcess);
		}
		/* else: other macro -> ignored */
		
	/* Tests if the macro found is "#end" or if we're at the end of the file */
	}while(vEnd && (vLengthRead > 0));
	
	if(vEnd)
	{
		printf("Warning: calculation \"%s\" was not ended by \"#end\" \n",sCalculation.name);
	}
	
	//~ *************************
	//~ TESTER SI Y'A DES PROCESS SINON LUI DIRE QU'IL EST VIDE
	//~ *************************
	
	/* Gives the calculation a number */
	sCalculation.index = vNbcalculations;
	
	/* Masks unused variables */
	//~ (t_whereami*) fgsfds;
	
	/* free reserved memory */
	free((void*)sCalculation.lsprocess);
}

int fLinkCharToFunc(int  carac,t_list* sFuncToLink, t_tools * p_Tools)
{
	int vIndex, vTest = 0;

	if(!strncomp(p_Tools->Buffer,"(",1);
	{
		
	}
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

int fgetline(FILE* p_file, unsigned int* n,char**p_string)
{
	unsigned int new_n = 0,stringlen;
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
		//~ printf("%3d--%c\n",c,c);
		*(*p_string + new_n) = (char)c;
		new_n++;
	}
	*(*p_string+new_n-1) = '\0';
	if(new_n > *n)
	{
		*n = strlen(*p_string);
		p_string = (char**)realloc(p_string,stringlen);
		if(p_string ==NULL)
		{
			printf("Out of memory\n");
			exit(-1);
		}
	}
	return new_n;
}

void InitMacroTable(t_tools * Tools)
{
	unsigned int vIndex,vTest;
	char script[NB_MACRO][STRMAXSIZE]={
	#include "../include/macrotable.h"
	};
	
	Tools->MaxMacroLength = 0;
	for(vIndex=0;vIndex<NB_MACRO;vIndex++)
	{
		vTest = strlen(script[vIndex]);
		if(vTest > Tools->MaxMacroLength)
		{
			Tools->MaxMacroLength = vTest;
		}
	}
	
	Tools->MaxStringSize = STRMAXSIZE;
	
	Tools->Buffer = (char*)gimmegimmegimme(sizeof(char),1,Tools->MaxMacroLength);
	if(Tools->Buffer == NULL)
	{
		printf("Out of memory\n");
		//~ exit(-1);
	}
	for(vIndex=0;vIndex<NB_MACRO;vIndex++)
	{
		Tools->MacroList[vIndex] = (char*)gimmegimmegimme(sizeof(char),1,Tools->MaxMacroLength);
		if(Tools->MacroList[vIndex] == NULL)
		{
			printf("Out of memory\n");
			//~ exit(-1);
		}
	}
	for(vIndex=0;vIndex<NB_MACRO;vIndex++)
	{
		Tools->MacroList[vIndex] = script[vIndex];
	}
	Tools->String = (char*)gimmegimmegimme(sizeof(char),1,Tools->MaxStringSize);
	if(Tools->String == NULL)
	{
		printf("Out of memory\n");
		//~ exit(-1);
	}
}

void fProcess(FILE * p_file, t_tools * p_Tools,  t_calculation * sCalculation, unsigned int * ProcessIndex)
{
	/* Used to verify the number of character read in standart string.h functions. */
	unsigned int vLengthRead;

	/* */
	unsigned int nbInstructionsDeclared = 0;
	
	/* General purpose index variable */
	unsigned int vIndex;
	
	/* General purpose test variable */
	unsigned int vTest;
	
	t_process * sProcess = sCalculation->lsprocess+(*ProcessIndex)-1;
	
	/* Gets the instruction list */
	vLengthRead = sscanf(p_Tools->String,"%*s %s",p_Tools->Buffer);
	
	/* If there is more than one instruction */
	if((vLengthRead > 0))
	{
		/* Temporary storage */
		t_list vTemp;
		
		vTest = 1;
		nbInstructionsDeclared =  0;
		/* If the user grouped the instructions within brackets, it is taken into account */
		if(!strncmp(p_Tools->Buffer,"{",1))
		{
			for(vIndex=0;(vIndex < p_Tools->MaxStringSize)&&(vTest)&&(strncmp(p_Tools->Buffer+vIndex,"\0",1));vIndex++)
			{
					
				if(fLinkCharToFunc(*(p_Tools->Buffer+vIndex),&vTemp))
				{
					/* Keeps track of the number of instructions declared */
					nbInstructionsDeclared++;
					/* Gets enough memory to store the new function pointer */
					sProcess->p_instructions = ( void(**)() )realloc( sProcess->p_instructions,(nbInstructionsDeclared+1)* sizeof(void(**)()));
					if(sProcess->p_instructions == NULL)
					{
						printf("Out of memory\n");
						exit(-1);
					}
					
					/* Links the character to the correct function using the link table */
					*(sProcess->p_instructions+nbInstructionsDeclared) = vTemp.instructions->func;
				}
				vTest = strncmp(p_Tools->Buffer+vIndex,"}",1);
			}
			
			//~ TESTER SI LA LECTURE PROCESS EST BONNE?
			sProcess->index = *ProcessIndex;
			if(vTest)
			{
				printf("Warning: instruction list in process #%d was not terminated by \"}\" \n",sCalculation->lsprocess->index);
			}
		}
		else
		{
			for(vIndex=0;(vIndex<vLengthRead)&&(vTest == 1);vIndex++)
			{
				vTest = fLinkCharToFunc(*(p_Tools->String+vIndex),&vTemp);
			}
			nbInstructionsDeclared++;
		}
		sProcess->nbinstructions = nbInstructionsDeclared;
		
		/* Shows the number of instructions found per process */
		//~ printf("--%d\n",nbInstructionsDeclared);
	}
	
	vLengthRead = fscanf(p_file,"%u",&vTest);
	if(vLengthRead > 1)
	{
		for(vIndex = 1;(vIndex <vTest)&&(vIndex < sCalculation->nbprocesses);vIndex++)
		{
			*(sCalculation->lsprocess+vIndex)= *(sCalculation->lsprocess);
		}
	}
}

void fGetNBProcess(FILE * p_file,t_tools * p_Tools, unsigned int * nbProcessDeclared)
{
	unsigned int vEnd = 0;
	unsigned int vTest = 0;
	unsigned int vLengthRead = 0;
	fpos_t stream_pos;
	
	/* Save the position of the stream indicator */
	vTest= fgetpos(p_file,&stream_pos);
	if(vTest)
	{
		printf("Error reading file\n");
		//~ exit(-1);
	}
	else
	{
		*nbProcessDeclared = 0;
		do
		{
			vLengthRead = fgetline(p_file,&p_Tools->MaxStringSize,&p_Tools->String);
			if(vLengthRead > 0)
			{
				/* '8' here is the number of characters in "#process" */
				sscanf(p_Tools->String,"%8s",p_Tools->Buffer);
				/* The other macros are ignored */
				if(!strncmp(p_Tools->Buffer,"#process",1))
				{
					if(!strncmp(p_Tools->Buffer,"#process",8))
					{
						*nbProcessDeclared+=1;
					}
					else
					{
						vEnd = 1;
					}
				}
			}
		}while(!vEnd && (vLengthRead > 0));
	}
	/* Restores the position of the stream indicator */
	vTest= fsetpos(p_file,&stream_pos);
	if(vTest)
	{
		perror("The following error occured: ");
		//~ exit(-1);
	}
}

/* EOF */
