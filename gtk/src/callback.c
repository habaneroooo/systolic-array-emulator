#include "../include/interface.h"
#include <glib.h>
#include <glib/gprintf.h>
#include <glib/gstdio.h>


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
	//~ t_MainWindow* p_p_MainWindow = static_cast<t_MainWindow*>(user_data);
	//~ char* p_char = static_cast<char*>(user_data);
	FILE * p_file = fopen(gtk_file_chooser_get_filename((GtkFileChooser *)p_widget), "r");
	if (p_file == NULL)
	{
		gtk_text_buffer_insert_at_cursor(gtk_text_view_get_buffer(GTK_TEXT_VIEW((static_cast<t_MainWindow*>(user_data))->textview)),
			_("Error opening file.\nPlease check if you have proper reading access to the file/directory.\n"),
			-1);
	}
	else 
	{
		gchar * p_buffer = (char *)malloc(sizeof(gchar)*ROW_SIZE);
				
		for(i=0;(i<ROW_SIZE)&& (bytesread==1);i++)
		{
			bytesread = fscanf(p_file, "%s",p_buffer);
			fprinttextview(static_cast<t_MainWindow*>(user_data),p_buffer);
		}
		
		free(p_buffer);
		fclose(p_file);
	}
	
	//~ GtkWidget * p_window = NULL;
	//~ p_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	//~ gtk_widget_show(p_window);
}

void cb_clear_textview_button(GtkWidget * p_widget, gpointer user_data)
{
	gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW((static_cast<t_WindowList*>(user_data))->main.textview))," ",0);
}

void cb_show_result_window(GtkWidget * p_widget, gpointer user_data)
{
	/* Shows everything declared before */
	gtk_widget_show_all((static_cast<t_WindowList*>(user_data))->result.window);
	/* */
	fprinttextview(&((static_cast<t_WindowList*>(user_data))->main),(gchar*)_("**\tOpening Results window\t**\n"));
}

void cb_hide_result_window(GtkWidget * p_widget, gpointer user_data)
{
	/* Shows everything declared before */
	gtk_widget_hide_all((static_cast<t_WindowList*>(user_data))->result.window);
	fprinttextview(&((static_cast<t_WindowList*>(user_data))->main),(gchar*)_("**\tClosing Results window\t**\n"));
}

void cb_save_window(GtkWidget * p_widget, gpointer user_data)
{
	gint vTest = FALSE;
	gint vTestResponse = 0;
	//~ gchar responsetype[50];
	
	/* Creates the "save file" dialog */
	fCreateWindow_save(&(static_cast<t_WindowList*>(user_data)->save));
	
	/* Shows everything declared before */
	gtk_widget_show((static_cast<t_WindowList*>(user_data))->save.save_file_chooser);
	
	/* Wait for a response */
	while(
		(vTest == FALSE) 
		&& 
		(vTestResponse = gtk_dialog_run(GTK_DIALOG(static_cast<t_WindowList*>(user_data)->save.save_file_chooser)))
		)
	{
		//~ sprintf(responsetype,"RESPONSE:%d\n",vTestResponse);
		//~ fprinttextview(static_cast<t_MainWindow*>(user_data),responsetype);
		switch(vTestResponse)
		{
			case GTK_RESPONSE_ACCEPT:		
											vTest = TRUE;
											break;
			case GTK_RESPONSE_CANCEL:		
			case GTK_RESPONSE_CLOSE:			
			case GTK_RESPONSE_DELETE_EVENT:		
			case GTK_RESPONSE_NONE:			
			default:							vTest = TRUE;
											break;
		}
	}
	gtk_widget_destroy(static_cast<t_WindowList*>(user_data)->save.save_file_chooser);
}

void fprinttextview(t_MainWindow* p_s_MainWindow,gchar* p_toprint)
{
	gtk_text_buffer_insert_at_cursor(gtk_text_view_get_buffer(GTK_TEXT_VIEW(p_s_MainWindow->textview)),p_toprint,-1);
}

/* EOF */
