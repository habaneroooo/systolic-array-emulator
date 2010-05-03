#ifndef __INTERFACE__
#define __INTERFACE__

#include <gtk/gtk.h>
#include <gio/gio.h>
#include <libintl.h> 
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#define _(string) gettext(string)

#define PROGRAM_NAME _("Systolic array emulator")

#define LARG 800
#define HAUT 600
#define LARG_RESULT 800
#define HAUT_RESULT 600
#define LARG_SAVE LARG/2
#define HAUT_SAVE HAUT/2
#define LEFT_MARGIN 4
#define RIGHT_MARGIN LEFT_MARGIN
#define TOP_MARGIN 4
#define BOTTOM_MARGIN TOP_MARGIN
#define SPACE_BETWEEN_ELEMENTS 4
#define GUTTER_SIZE 100
#define LARG_BUTTONS ((LARG/2)-(SPACE_BETWEEN_ELEMENTS*3/2)-(LEFT_MARGIN))/2

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

void fCreateWindow_main(t_MainWindow*);
void fCreateWindow_results(t_ResultWindow*);
void fCreateWindow_save(t_SaveWindow*);

#include "../include/callback.h"

#endif /* EOF */
