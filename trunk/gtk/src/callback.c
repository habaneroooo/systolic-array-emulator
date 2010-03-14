#include <gtk/gtk.h>
#include <gio/gio.h>

#include <glib.h>
#include <glib/gprintf.h>
#include <glib/gstdio.h>

#include <stdio.h>
#include <stdlib.h>

#include "../include/interface.h"
#include "../include/callback.h"

void* todo[ROW_SIZE][ROW_SIZE];

void cb_quit (GtkWidget *p_widget, gpointer user_data)
{
	gtk_main_quit();
	/* Parametres inutilises */
	(void)p_widget;
	(void)user_data;
}

void cb_input_file_button (GtkWidget * p_widget, gpointer user_data)
{
	int bytesread=1;
	int i;
	FILE * p_file = fopen(gtk_file_chooser_get_filename((GtkFileChooser *)p_widget), "r");
	if (p_file == NULL)
	{
		printf("Error opening file\nPlease check if your read rights are correctly set.\n");
		exit(-1);
	}
	else 
	{
		char * p_buffer = (char *)malloc(sizeof(short)*ROW_SIZE);
		for(i=0;(i<ROW_SIZE)&& (bytesread==1);i++)
		{
			bytesread = fscanf(p_file, "%s",p_buffer);
			g_printf("%d\n",bytesread);
		}
		
		free(p_buffer);
		fclose(p_file);
	}
	
	//~ GtkWidget * p_window = NULL;
	//~ p_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	//~ gtk_widget_show(p_window);
	
	/* Parametres inutilises */
	(void)user_data;
}

/* EOF */
