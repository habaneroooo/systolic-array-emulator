#include "../include/script.h"

int fParseFile(FILE * p_file)
{
	unsigned int vTest = 1;
	int vIndex;
	int vLengthRead;
	int vNbcalculations = 0;
	
	t_tools Tools;
	t_whereami fgsfds = begin;
	char script[NB_MACRO][MAXMACROLENGTH+1]={"#calculation","#row","#end"};

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
		Tools.line = 0;
		Tools.Buffer = (char*)malloc(sizeof(char)*Tools.MaxMacroLength+1);
		if(Tools.Buffer == NULL)
		{
			printf("Out of memory\n");
			//~ exit(-1);
		}
		for(vIndex=0;vIndex<NB_MACRO;vIndex++)
		{
			Tools.MacroList[vIndex] = (char*)malloc(sizeof(char)*Tools.MaxMacroLength);
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
		Tools.CurrentStringSize = Tools.MaxStringSize;
		Tools.String = (char*)malloc(sizeof(char)*Tools.MaxStringSize);
		if(Tools.String == NULL)
		{
			printf("Out of memory\n");
			//~ exit(-1);
		}
		/* Remplacer par "si pas d'erreurs" */
		else
		{
			/* This test always finds the first macro in the script file */
			do
			{
				Tools.CurrentStringSize = fgetline(p_file,&Tools.MaxStringSize,&Tools.String,&Tools.line);
			}while(*Tools.String != '#');
			vLengthRead = sscanf(Tools.String,"%s",Tools.Buffer);
			
			/* Permet de trouver la macro que l'on a lu. */
			for(vIndex = 0;(vIndex < NB_MACRO) &&  (vTest != 0 );vIndex++)
			{
				vTest = strcmp(Tools.Buffer,Tools.MacroList[vIndex]);
			}
			if(vTest == 0)	
			{
				switch(vIndex)
				{
					case begin:			break;
					
					case calculation:		fgsfds = calculation;
										if(fGetCalculation(&fgsfds,p_file,vNbcalculations,&Tools))
										{
											vNbcalculations++;
											/* retenir qu'il y a eu des erreurs et free la memoire réservée */
										}
										break;
					
					default:				/* This can only happen if you have not the same number of */
										/* macros declared and defined in NB_MACRO (script.h) */
										printf("Macro \"%s\" undefined: the parser is bugged.\nIgnoring\n",Tools.String);
				}
			}
			else
			{
				printf("Not found\n");
			}
		}
		
		/* Clear dynamically declared memory space */
		
	} /* end check opening file */
	
	return 0;
}

/*
 * fCalculation():
 * Scans trough the script file for processes and allocates memory according to what's written inside that file
 *
 * Arguments:
 * (void*)	fgsfds: the context variable
 * (FILE*)	p_file: the script file
 * (int)	vNbcalculations:
 * (char*)	script: A list of the known macros.
 * (char*)	p_string: General string used to read through the script file
 * (int*)	p_vMaxStringSize: the current length of p_string
 */
int fGetCalculation(t_whereami* fgsfds, FILE * p_file, int vNbcalculations, t_tools * p_Tools)
{
	/* The calculation we're about to read */
	//~ MAKE THIS A POINTER AND HAVE IT RETURN AN ERROR CODE IF NEEDED
	t_calculation sCalculation;
	
	/* Used to verify the number of character read in standard string.h functions. */
	unsigned int vLengthRead;
	
	/* General purpose test variables */
	unsigned int vTest = 1;
	unsigned int vTest2 = 1;
	//~ unsigned int vEnd = 1;
	int vIsProperlyDeclared = 1;
	
	/* Gets the name & number of processes */
	p_Tools->String++;
	
	/* Scans the opened file for the calculation name */
	//~ POSSIBILITE DE BUG SUR LA LONGUEUR
	sCalculation.name = (char*)malloc(sizeof(char)*p_Tools->MaxStringSize);
	vLengthRead = sscanf(p_Tools->String,"%*s %s",sCalculation.name);
	
	/* Verifies the calculation does have a name... */
	if(vLengthRead == 0)
	{
		sCalculation.name = (char*)realloc(sCalculation.name,sizeof(char));
		sprintf(sCalculation.name,"%c",(char)vNbcalculations+1+'0');
		printf("Warning: #calculation with no name\nRenamed \"%s\"\n",sCalculation.name);
	}
	
	/* This test always finds the first macro in the calculation */
	/* Gets the matrix size */
	vTest = 1;
	//~ vTest2 = 1;
	do
	{
		vLengthRead = fgetline(p_file,&p_Tools->MaxStringSize,&p_Tools->String,&p_Tools->line);
		sscanf(p_Tools->String,"%4s",p_Tools->Buffer);
		vTest = strncmp(p_Tools->Buffer,"#row",1);
	}while(vTest && (vLengthRead > 0) && !vTest2);
	
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
				*fgsfds = begin;
				vIsProperlyDeclared = 0;
				return vIsProperlyDeclared;
			}
			else
			{
				sCalculation.nbprocesses=0;
				sCalculation.lsprocess = (t_process*)malloc(sizeof(t_process));
				if(sCalculation.lsprocess == NULL)
				{
					printf("Out of memory.\n");
					exit(-1);
				}
				
				/* Gets the number of process declared */
				/* WARNING: meaning of vTest switched to "reading errors" */
				/* RETOURNER UNE ERREUR */
				fParseCalculation(p_file,p_Tools,&sCalculation);
				
				while(1);
				
				/* Tests*/
				if(!sCalculation.nbprocesses)
				{
					printf("Error: Empty calculation \"%s\"\nIgnoring calculation.\n",sCalculation.name);
					*fgsfds = begin;
					vIsProperlyDeclared = 0;
					return vIsProperlyDeclared;
				}
			}
		}
		else if(!strcmp(p_Tools->Buffer,"#cal"))
		{
			sscanf(p_Tools->String,"%12s",p_Tools->Buffer);
			if(!strcmp(p_Tools->Buffer,"#calculation"))
			{
				printf("Warning: calculation \"%s\" was not ended by \"#end\" \n",sCalculation.name);
				
				/* /!\ Recursive call here /!\ */
				vIsProperlyDeclared = fGetCalculation(fgsfds,p_file,vNbcalculations,p_Tools);
				*fgsfds = begin;
				return vIsProperlyDeclared;
			}
			else
			{
				printf("Error: Unknown macro \"%s\"",p_Tools->Buffer);
				*fgsfds = begin;
				vIsProperlyDeclared = 0;
				return vIsProperlyDeclared;
			}
		}
	}
	/* Currently, the parser will ignore a calculation if the rowsize was not specified */
	else
	{
		printf("Error: the matrix size for calculation %s was not specified.\n",sCalculation.name);
		printf("Ignoring calculation.\n");
		*fgsfds = begin;
		vIsProperlyDeclared = 0;
		return vIsProperlyDeclared;
	}
	
	/* Gives the calculation a number */
	sCalculation.index = vNbcalculations;
	
	/* free reserved memory */
	return vIsProperlyDeclared;
}

void fParseCalculation(FILE * p_file,t_tools * p_Tools, t_calculation * sCalculation)
{
	unsigned int vEndParse = 0;
	unsigned int vTest = 0;
	unsigned int vIndex = 0;
	unsigned int vShift = 0;
	unsigned int vShiftSuperString = 0;
	int vLengthRead = 0;
	fpos_t stream_pos;
	char * SuperString = (char*)malloc(300*sizeof(char));
	
	/* Save the position of the stream indicator */
	vTest= fgetpos(p_file,&stream_pos);
	if(vTest)
	{
		printf("Error reading file\n");
		//~ exit(-1);
	}
	else
	{	
		p_Tools->context = calculation;
		p_Tools->Buffer = (char*)realloc(p_Tools->Buffer,p_Tools->MaxStringSize);
		if(p_Tools->Buffer == NULL)
		{
			printf("Out of memory\n");
			//~ exit(-1);
		}
		do
		{
			/* Gets a new line to parse */
			vLengthRead = fgetline(p_file,&p_Tools->MaxStringSize,&p_Tools->String,&p_Tools->line);
			/* Removes the '\0' character */
			vLengthRead -=1;
			
			if(vLengthRead > 0)
			{
				vIndex = 0;
				vShift = 0;
				
				/* Parse one line */
				do
				{
					/* gets one character */
					sscanf(p_Tools->String+vIndex,"%c",p_Tools->Buffer);
										
					if(!strncmp(p_Tools->Buffer,TOKEN_BEGIN_PROCESS,1))
					{
						if(p_Tools->context == calculation)
						{
							p_Tools->context = process;
							
							vShift=1;
						}
						else
						{
							printf("Syntax error at line %ld\n",p_Tools->line);
							vEndParse = 1;
							//~ exit(-1);
						}
					}
					else if(!strncmp(p_Tools->Buffer,TOKEN_END_PROCESS,1))
					{
						sscanf(p_Tools->String+vIndex,"%2s",p_Tools->Buffer);
						if(p_Tools->context == process)
						{
							p_Tools->context = calculation;
							
							/* Prints out the result of the scanning - for test purpose */
							//~ {
								//~ unsigned int i;
								//~ for(i=0;i<vShiftSuperString;i++)
									//~ putchar(*(SuperString+i));
								//~ putchar('\n');
							//~ }
							
							if(fVerifyProcessDeclaration(p_Tools,SuperString,vShiftSuperString,sCalculation) == TTRUE)
							{
								sCalculation->nbprocesses++;
								sCalculation->lsprocess = (t_process*)realloc(sCalculation->lsprocess,sCalculation->nbprocesses+1);
								if(sCalculation->lsprocess == NULL)
								{
									printf("Out of memory.\n");
									exit(-1);
								}
							}
							else
							{
								/* RETOURNER UNE ERREUR PLUTOT */
								//~ printf("Error at line %ld\n",p_Tools->line);
							}
							vShiftSuperString = 0;
							vShift = 2;
						}
						else
						{
							printf("Syntax error at line %ld\n",p_Tools->line);
							vShift = 2;
							vEndParse = 1;
							//~ exit(-1);
						}
					}
					else if(!strncmp(p_Tools->Buffer,TOKEN_END_CALCULATION,1))
					{
						sscanf(p_Tools->String+vIndex,"%3s",p_Tools->Buffer);
						if(!(p_Tools->context == calculation) && !strncmp(p_Tools->Buffer,TOKEN_END_CALCULATION,sizeof(TOKEN_END_CALCULATION)))
						{
							printf("Syntax error at line %ld\n",p_Tools->line);
							vShift = sizeof(TOKEN_END_CALCULATION);
							vEndParse = 1;
							//~ exit(-1);
						}
						else
						{
							*(SuperString+vShiftSuperString) = *p_Tools->Buffer;
							vShiftSuperString++;
							
							vShift = 1;
						}
					}
					else
					{
						vShift = 1;
						if(*p_Tools->Buffer == '\x0A')
						{
							p_Tools->line++;
						}
						else if(p_Tools->context == process)
						{
							*(SuperString+vShiftSuperString) = *p_Tools->Buffer;
							vShiftSuperString++;
						}
					}
					vIndex += vShift;
					vLengthRead -= vShift;
				}while((vLengthRead > 0) && (vEndParse == 0));
			} /* end if vLengthRead == 0 */
			else
			{
				vEndParse = 1;
			}
		}while(!vEndParse);
	}
	/* Restores the position of the stream indicator */
	vTest= fsetpos(p_file,&stream_pos);
	if(vTest)
	{
		perror("The following error occured: ");
		//~ exit(-1);
	}
	
	/*Leave this here for testing purposes */
	//~ printf("Found %d process\n",sCalculation->nbprocesses,SuperString);
}

/* EOF */
