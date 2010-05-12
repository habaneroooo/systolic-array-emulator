#ifndef __TYPES__
#define __TYPES__

#include <gtk/gtk.h>
#include <gio/gio.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <glib/gstdio.h>
#include <ctype.h>

#define NB_MACRO 3
#define MAX_REGISTER_TOKEN_LENGTH 4
#define MAX_INSTRUCTION_TOKEN_LENGTH 3

typedef enum {begin,calculation,after_calculation,register_,process} t_whereami;

typedef void (*t_func)(void);

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
	void (*func)();
	unsigned char NbMinDataIn;
	unsigned char NbMaxDataIn;
}t_list;

typedef struct{
	GtkWidget * window;
	GtkWidget * fixed;
	GtkWidget * frame;
	GtkWidget * scrolled_window;
	GtkWidget * textview;
	//~ GtkWidget * frame_button_file_chooser;
	GtkWidget * button_file_chooser;
	GtkWidget * file_chooser;
	GtkWidget * button_start_parse;
	GtkWidget * button_clear_message_window;
	GtkWidget * button_save_log;
	GtkWidget * button_show_result_window;
}t_MainWindow;

typedef struct{
	GtkWidget * window;
	GtkWidget * hpaned;
	GtkWidget * scrolled_window;
	GtkWidget * left_fixed;
	GtkWidget * right_fixed;
	GtkWidget * button_close;
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
	FILE * file;
	int FileOpened;
	t_calculation * CalculationList;
	int NBCalculations;
	t_WindowList WindowList;
}t_toolbox;

#endif

/* EOF */
