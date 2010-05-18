#ifndef __TYPES__
#define __TYPES__

#include <gtk/gtk.h>
#include <gio/gio.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <glib/gstdio.h>
#include <gdk-pixbuf/gdk-pixdata.h>
#include <pthread.h>
#include <ctype.h>

#define NB_MACRO 3
#define MAX_REGISTER_TOKEN_LENGTH 4
#define MAX_INSTRUCTION_TOKEN_LENGTH 3
#define SHOW_REGISTERS_IN_RESULT_WINDOW TRUE

#define TTRUE 1
#define FFALSE 0

#define STRMAXSIZE 100
#define MAX_NB_PROCESS_IFNDEF 42
#define MAX_NB_INSTRUCTIONS 42
#define BUFFERSIZE 12
#define MAXMACROLENGTH 12
#define FREE_AND_EXIT_VERIFY_PROCESS {	free(Process);	free(Instruction);	free(Buffer3);	return vIsProperlyDeclared;	}

#define NBINSTRUCTIONS 9

#define TOKEN_BEGIN_PROCESS "<"
#define TOKEN_END_PROCESS ">;"
#define TOKEN_END_CALCULATION "end"

#define NB_REG 32
#define NB_STATIC_REG 6

#define NB_MAX_PROCESS 10

typedef enum {begin,calculation,after_calculation,register_,process} t_whereami;

typedef void (*t_func)(int *, int *, int);

typedef struct {
	bool * hmask;
	bool * vmask;
	int reg_out;
	int * reg_in;
	int nb_reg_in;
	t_func p_instructions;
}t_process;

typedef struct {
	char * name;
	unsigned int index;
	unsigned int rowsize;
	unsigned int nbprocesses;
	t_process * lsprocess;
}t_calculation;

typedef struct {
	t_whereami context;
	char* Buffer;
	unsigned int MaxStringSize;
	char* MacroList[NB_MACRO];
	unsigned int MaxMacroLength;
	char * String;
	long CurrentStringSize;
}t_tools;

typedef struct
{
	char reg[MAX_REGISTER_TOKEN_LENGTH];
	int num;
}t_reg;

typedef struct {
	char carac[MAX_INSTRUCTION_TOKEN_LENGTH+1];
//	void (*func)();
	t_func func;
	unsigned char NbMinDataIn;
	unsigned char NbMaxDataIn;
}t_list;

typedef struct{
	GtkSettings * settings;
	GtkWidget * window;
	GtkWidget * fixed;
	GtkWidget * frame;
	GtkWidget * scrolled_window;
	GtkWidget * textview;
	GtkWidget * combobox;
	GtkWidget * button_file_chooser;
	GtkWidget * file_chooser;
	GtkWidget * button_start_parse;
	GtkWidget * button_clear_message_window;
	GtkWidget * button_save_log;
	GtkWidget * button_show_result_window;
	GtkWidget * button_close;
}t_MainWindow;

typedef struct{
	GtkWidget * window;
	GtkWidget * hpaned;
	GtkWidget * scrolled_window;
	GtkWidget * left_fixed;
	GtkWidget * right_fixed;
	GtkWidget * button_close;
	GtkWidget * button_start_execute;
	GtkWidget ** image_proc;
#if SHOW_REGISTERS_IN_RESULT_WINDOW == TRUE
	GtkWidget ** entry;
#else
	GtkWidget ** image_reg_right;
	GtkWidget ** image_reg_down;
#endif
}t_ResultWindow;

typedef struct{
	GtkWidget * save_file_chooser;
}t_SaveWindow;

typedef struct{
	t_MainWindow main;
	t_ResultWindow result;
	t_SaveWindow save;
}t_WindowList;

typedef struct
{
	gint threadID;
//	void (*func)();
	t_func func;
	gint reg[NB_REG+NB_STATIC_REG];
	gint reg_out;
	gint *reg_in;
	gint nb_reg_in;
	gint quit;
	pthread_barrier_t * barrier;
}__attribute__((aligned(sizeof(gint)))) t_Args;

typedef struct
{
	pthread_t * Handler;
	pthread_t * ThreadArray;
	t_Args * ArgsArray;
	pthread_barrier_t barrier;
	pthread_cond_t depart_handler;
	pthread_mutex_t mutex_depart_handler;
}t_Handler;

typedef struct
{
	FILE * file;
	gint FileOpened;
	gint NBCalculations;
	gint iParsed;
	gint iShowed;
	gint SelectCalculation;
	t_calculation * CalculationList;
	t_WindowList WindowList;
	t_Args * MyArgs;
	t_Handler systolic_array;
}t_toolbox;

#endif

/* EOF */
