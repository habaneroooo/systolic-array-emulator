#ifndef __INSTRUCTIONS__
#define __INSTRUCTIONS__

void fvoid(int *, int *, int);
void print_threadid(int *, int *, int);

/*
 * Global variables declaration go here
 * Try not to declare too many - use pointers instead.
 */
const t_list tab_list[NBINSTRUCTIONS] = 
{
		{"add",print_threadid,2,0xFF},
		{"*",print_threadid,2,0xFF},
		{"-",fvoid,2,100},
		{"/",fvoid,2,0xFF},
		{"�",fvoid,2,0xFF},
		{"%",fvoid,2,0xFF},
		{"&",fvoid,2,0xFF},
		{"|",fvoid,2,0xFF},
		{"set",fvoid,3,0xFF}
};

const t_reg Registers[NB_STATIC_REG] =
{
	{"C",NB_REG+0},
	{"CW",NB_REG+1},
	{"CN",NB_REG+2},
	{"CE",NB_REG+3},
	{"CS",NB_REG+4},
	{"REG",0}
};
#endif /* EOF */
