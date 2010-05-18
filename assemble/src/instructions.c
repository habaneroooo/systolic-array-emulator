#include "../include/types.h"
//
#include "../include/interface.h"
#include "../include/parser.h"
#include "../include/instructions.h"

void print_threadid(int * dest, int * src, int nb_src)
{
	gint vIndex;
	for(vIndex = 0; vIndex < nb_src;vIndex++)
	{
		/* Add in your function here*/
		*dest = *(src+nb_src);
	}
}

void inst2(void)
{
	g_printf("2");
}

void inst3(void)
{
	g_printf("3");
}

void inst4(void)
{
	g_printf("4\n");
}

void fvoid(int * dest, int *, int)
{
	*dest = 42;
}

/* EOF */
