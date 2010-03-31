#ifndef __LINK__
#define __LINK

/*
 * Includes go here
 */
#include "script.h"
#include "instructions.h"

/*
 * Macro definitions go here
 */
#define NBINSTRUCTIONS 11

/*
 * Custom types definitions go here
 */

typedef struct {
	char type[3];
	void (*func)();
}t_sublist;

typedef struct {
	char carac;
	t_sublist instructions[7];

}t_list;

/*
 * Global variables declaration go here
 * Try not to declare too many - use pointers instead.
 */
const t_list tab_list[NBINSTRUCTIONS] = 
{
		{'*',{
				{"ul",fvoid},
				{"sl",fvoid},
				{"ud",fvoid},
				{"sd",fvoid},
				{"us",fvoid},
				{"ss",fvoid},
				{"f",fvoid},
			}
		},
		{'>',{
				{"ul",fvoid},
				{"sl",fvoid},
				{"ud",fvoid},
				{"sd",fvoid},
				{"us",fvoid},
				{"ss",fvoid},
				{"f",fvoid},
			}
		},
		{'<',{
				{"ul",fvoid},
				{"sl",fvoid},
				{"ud",fvoid},
				{"sd",fvoid},
				{"us",fvoid},
				{"ss",fvoid},
				{"f",fvoid},
			}
		},
		{'+',{
				{"ul",fvoid},
				{"sl",fvoid},
				{"ud",fvoid},
				{"sd",fvoid},
				{"us",fvoid},
				{"ss",fvoid},
				{"f",fvoid},
			}
		},
		{'-',{
				{"ul",fvoid},
				{"sl",fvoid},
				{"ud",fvoid},
				{"sd",fvoid},
				{"us",fvoid},
				{"ss",fvoid},
				{"f",fvoid},
			}
		},
		{'/',{
				{"ul",fvoid},
				{"sl",fvoid},
				{"ud",fvoid},
				{"sd",fvoid},
				{"us",fvoid},
				{"ss",fvoid},
				{"f",fvoid},
			}
		},
		{'ø',{
				{"ul",fvoid},
				{"sl",fvoid},
				{"ud",fvoid},
				{"sd",fvoid},
				{"us",fvoid},
				{"ss",fvoid},
				{"f",fvoid},
			}
		},
		{'%',{
				{"ul",fvoid},
				{"sl",fvoid},
				{"ud",fvoid},
				{"sd",fvoid},
				{"us",fvoid},
				{"ss",fvoid},
				{"f",fvoid},
			}
		},
		{'&',{
				{"ul",fvoid},
				{"sl",fvoid},
				{"ud",fvoid},
				{"sd",fvoid},
				{"us",fvoid},
				{"ss",fvoid},
				{"f",fvoid},
			}
		},
		{'|',{
				{"ul",fvoid},
				{"sl",fvoid},
				{"ud",fvoid},
				{"sd",fvoid},
				{"us",fvoid},
				{"ss",fvoid},
				{"f",fvoid},
			}
		}
	};
	
#endif
	
/* EOF */
	
