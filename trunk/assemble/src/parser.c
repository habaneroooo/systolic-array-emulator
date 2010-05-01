#include "../include/parser.h"

int fVerifyProcessDeclaration(t_tools * p_Tools,char * ProcessToParse, unsigned int vLength, t_calculation * sCalculation)
{
	char vIsProperlyDeclared = TRUE;
	unsigned int vLengthRead = 0;
	unsigned int vNBArgsFound = 0;
	int vShift = 0;
	int vShift2 = 0;
	int vEnd = 0;
	unsigned int i = 0;
	
	char * Instruction = (char*)malloc(sizeof(char)*vLength+1);
	char * Buffer3 = (char*)malloc(sizeof(char)*vLength+1);
	char * Process = (char*)malloc(sizeof(char)*vLength+1);
	strncpy(Process,ProcessToParse,vLength);
	strcat(Process,"\0");
	
	/* I need this because of lvalue assignments errors */
	t_process ** p_process = &(sCalculation->lsprocess);
	*p_process += sCalculation->nbprocesses;
	
	p_Tools->Buffer = (char*)realloc(p_Tools->Buffer,sizeof(char)*vLength+1);
	if(p_Tools->Buffer == NULL)
	{
		printf("Out of memory\n");
		exit(-1);
	}
	
	/* Removes semicolumn, gets the string before */
	/* If none, no checking is done at the moment */
	vLengthRead = strcspn(Process,";");
	if(vLengthRead <= 0)
	{
		vIsProperlyDeclared = 0;
		printf("Error: No instruction specified\n");
		
		FREE_AND_EXIT_VERIFY_PROCESS
	}
	else
	{
		p_Tools->Buffer = (char*)realloc(p_Tools->Buffer,vLengthRead+1);
		memset(p_Tools->Buffer,'\0',vLengthRead+1);
		strncpy(p_Tools->Buffer,Process,vLengthRead);
	}
	
	/*Gets the instruction, removes whitespaces */
	{
		vLengthRead = 0;
		vShift = 0;
		while((vLengthRead == 0)&&(vShift < (int)strlen(p_Tools->Buffer)))
		{
			vLengthRead = strcspn(p_Tools->Buffer+vShift,"	 ;");
			if(!vLengthRead)
				vShift++;
		}
		
		if(vLengthRead <= 0)
		{
			vIsProperlyDeclared = 0;
			printf("Error: No instruction specified\n");
			
			FREE_AND_EXIT_VERIFY_PROCESS
		}
		else
		{
			Instruction = (char*)realloc(Instruction,vLengthRead+1);
			if(Instruction == NULL)
			{
				printf("Out of memory\n");
				exit(-1);
			}
			memset(Instruction,'\0',vLengthRead+1);
			strncpy(Instruction,p_Tools->Buffer+vShift,vLengthRead);
			for(i=0;((i<NBINSTRUCTIONS)&&!vEnd);i++)
			{
				if(!strncmp(tab_list[i].carac,Instruction,vLengthRead))
					vEnd = 1;
			}
			i--;
		}
		if(vEnd == 0)
		{
			vIsProperlyDeclared = 0;
			printf("Error: Instruction \"%s\" unknown\n",Instruction);
			
			FREE_AND_EXIT_VERIFY_PROCESS
		}
		else
		{
			/* Initializes memory for reallocs comming next */
			(*p_process)->reg_in = (int*)malloc(sizeof(int));
			if((*p_process)->reg_in == NULL)
			{
				printf("Out of memory");
				exit(-1);
			}
		}
	}
	/* Checks the number of arguments of the function */
	{
		vShift += vLengthRead;
		vNBArgsFound = 0;
		
		/* Removes whitespaces */
		do
		{
			vShift2 = 0;
			if(vShift < (int)strlen(p_Tools->Buffer))
				vEnd = 0;
			do
			{
				if(!(vShift < (int)strlen(p_Tools->Buffer)))
					vEnd = 1;
				else
				{
					vShift2 = strcspn(p_Tools->Buffer+vShift,"	 ");
					if(vShift2 == 0)
						vShift++;
				
				}
			}while((vShift2 == 0) && !vEnd);
			if(!vEnd)
			{
				vShift2 = strcspn(p_Tools->Buffer+vShift,",;");
				if(vShift2 == 0)
				{
					vIsProperlyDeclared = 0;
					printf("Error: Missing argument %d for instruction \"%s\"\n",vLengthRead+1,Instruction);
					
					FREE_AND_EXIT_VERIFY_PROCESS
				}
				Buffer3 = (char*)realloc(Buffer3,vShift2+1);
				if(Buffer3 == NULL)
				{
					printf("Out of memory\n");
					exit(-1);
				}
				memset(Buffer3,'\0',vShift2+1);
				strncpy(Buffer3,p_Tools->Buffer+vShift,vShift2);

				vShift += vShift2+1;
				if(fTestRegisterValidity(&Buffer3,*p_process,vShift2,&vNBArgsFound))
				{
					vIsProperlyDeclared = 0;
					printf("Error: Invalid register \"%s\"\n",Buffer3);
					
					FREE_AND_EXIT_VERIFY_PROCESS
				}
			}
		}while((!vEnd) && (vShift < (int)strlen(p_Tools->Buffer)) && (vLengthRead <= tab_list[i].NbMaxDataIn));
		
		if(vNBArgsFound < tab_list[i].NbMinDataIn)
		{
			vIsProperlyDeclared = 0;
			printf("Error: Too few arguments for function \"%s\" (Min:%d)\n",Instruction,tab_list[i].NbMinDataIn);
			
			FREE_AND_EXIT_VERIFY_PROCESS
		}
		else if(vNBArgsFound > tab_list[i].NbMaxDataIn)
		{
			vIsProperlyDeclared = 0;
			printf("Too many arguments for function \"%s\" (Max:%d)\nIgnoring the exceeding parameters\n",Instruction,tab_list[i].NbMaxDataIn);
			
			FREE_AND_EXIT_VERIFY_PROCESS
		}
		else
		{
			unsigned int i = 0;
			vEnd = 1;
			
			for(i=0;( i < 2 ) && ( vEnd == 1);i++)
			{
				vLengthRead = strcspn(Process,";");
				
				if(i == 0)
				{
					vLength = strcspn(Process+vLengthRead+1,";");
					vShift2 = vLength;
				}
				else
				{
					vLength = strcspn(Process+vLengthRead+1+vShift2+1,";");
				}
				
				p_Tools->Buffer = (char*)realloc(p_Tools->Buffer,vLength+1);
				if(p_Tools->Buffer == NULL)
				{
					printf("Out of memory\n");
					exit(-1);
				}
				memset(p_Tools->Buffer,'\0',vLength+1);
				if(i == 0)
				{
					strncpy(p_Tools->Buffer,Process+vLengthRead+1,vLength);
					strcat(p_Tools->Buffer,"\0");
					(*p_process)->hmask = (bool*)malloc(sizeof(bool)*sCalculation->rowsize);
					memset((*p_process)->hmask,0,sCalculation->rowsize);
					vEnd = fVerifyProcessSelector(sCalculation,&(p_Tools->Buffer),vLength,&((*p_process)->hmask));
				}
				else
				{	
					strncpy(p_Tools->Buffer,Process+vLengthRead+1+vShift2+1,vLength);
					strcat(p_Tools->Buffer,"\0");
					(*p_process)->vmask = (bool*)malloc(sizeof(bool)*sCalculation->rowsize);
					memset((*p_process)->vmask,0,sCalculation->rowsize);
					vEnd = fVerifyProcessSelector(sCalculation,&(p_Tools->Buffer),vLength,&((*p_process)->vmask));
				}
			}
			if(vEnd == 0)
			{
				vIsProperlyDeclared = 0;
				FREE_AND_EXIT_VERIFY_PROCESS
			}
		}
		
		/*Leave this here for testing purposes */
		//~ if(vIsProperlyDeclared)
			//~ printf("Found %d arguments for function \"%s\"\n",vNBArgsFound,Instruction);
	}
	FREE_AND_EXIT_VERIFY_PROCESS
}

int fTestRegisterValidity(char **p_Buffer, t_process* p_process,int vLength,unsigned int * vNBArgsFound)
{
	int vIsValid = 1;
	int vIndex;
	for(vIndex=0;(vIndex < NBINSTRUCTIONS) && (vIsValid != 0);vIndex++)
	{
		vIsValid = strncmp(*p_Buffer,Registers[vIndex].reg,vLength);
		if(!vIsValid)
		{
			if(*vNBArgsFound == 0)
			{
				(*vNBArgsFound)++;
				p_process->reg_out = Registers[vIndex].num;
			}
			else
			{
				(*vNBArgsFound)++;
				/*Realloc bugs here */
				p_process->reg_in = (int*)malloc(sizeof(int)*((*vNBArgsFound)+1));
				if(p_process->reg_in == NULL)
				{
					printf("Out of memory.\n");
					exit(-1);
				}
								
				*(p_process->reg_in+((*vNBArgsFound) - 1)) = Registers[vIndex].num;
				(p_process->nb_reg_in)++;
			}
		}
	}
	return vIsValid;
}

/* this function receives the text in between two semicolumns (or a semicolumn and the end of the process declaration) */
unsigned int fVerifyProcessSelector(t_calculation * sCalculation,char ** Buffer,unsigned int vLength,bool** mask)
{
	unsigned int vShift2 = 0;
	unsigned int vShift = 0;
	unsigned int vOK = 1;
	int vEnd = 0;

	/* Removes whitespaces */
	/*The first 'if' is useless here but I don't want to have two different function for removing whitespaces */
	if(vShift < vLength)
		vEnd = 0;
	do
	{
		if(!(vShift < vLength))
			vEnd = 1;
		else
		{
			vShift2 = strcspn(*Buffer+vShift," 	");
			if(vShift2 == 0)
				vShift++;
		
		}
	}while((vShift2 == 0) && !vEnd);
	vLength = strcspn(*Buffer+vShift," 	");
	if(vLength == 0)
	{
		vOK = 0;
		printf("Error: Instruction selector missing\n");
		return vOK;
	}
	else if(isalnum(*(*Buffer+vShift)))
	{
		unsigned int i=0;
		char carac;
		if(vLength < sCalculation->rowsize)
		{
			printf("Warning: selector too small. The remaining parameters are set to '0'.\n");
		}
		else if(vLength > sCalculation->rowsize)
		{
			printf("Warning: selector too big. The exceeding parameters are ignored.\n");
		}
		
		/* Quelle variable contient le nombre de process déclarés jusqu'à présent? */
		do
		{
			carac = *(*Buffer+vShift+i);
			if(isalnum(carac) && (carac == '1' || carac == '0'))
				*(*mask+i) = atoi(&carac)&0x1;
			else
			{
				vOK = 0;
				printf("Error: character \"%c\" is forbidden in numeric selector.\nUse ONLY 1's and 0's\n",(int)carac);
				return vOK;
			}
			i++;
		}while(i < sCalculation->rowsize);
	}
	/* ADD [] AND ()() RECOGNITION HERE */
	else
	{
		
	}
	
	return vOK;
}

int fgetline(FILE* p_file, unsigned int* n,char**p_string, long* line)
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
	
	/* So we know where we are */
	*line++;
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

/* EOF */
