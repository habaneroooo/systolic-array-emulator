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
	GtkWidget* p_p_textview = (GtkWidget*)user_=data;
	FILE * p_file = fopen(gtk_file_chooser_get_filename((GtkFileChooser *)p_widget), "r");
	if (p_file == NULL)
	{
		gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(p_p_textview)),
			"Error opening file.\nPlease check if you have proper reading access to the file/directory.\n",
			-1);
		//~ g_printf("%s",(char*)user_data);
		//~ g_print("%s","salut");
		//~ exit(-1);
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
