#include <stdio.h>
#include <stdlib.h>

#include "../include/types.h"

#include "../include/parser.h"
#include "../include/interface.h"
#include "../include/script.h"
#include "../include/gettext.h"
#include "../include/callback.h"


void cb_quit (GtkWidget*, gpointer)
{
	gtk_main_quit();
}

void cb_input_file_button (GtkWidget *, gpointer user_data)
{
	t_WindowList p_WindowsList = (static_cast<t_toolbox*>(user_data))->WindowList;
	static_cast<t_toolbox*>(user_data)->FileOpened  = 1;
}

void cb_clear_textview_button(GtkWidget *, gpointer user_data)
{
	gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW((static_cast<t_WindowList*>(user_data))->main.textview))," ",0);
}

void cb_show_result_window(GtkWidget *, gpointer user_data)
{
	/* Shows everything declared before */
	gtk_widget_show_all((static_cast<t_WindowList*>(user_data))->result.window);
	fprinttextview(&((static_cast<t_WindowList*>(user_data))->main),(gchar*)_("**\tOpening Results window\t**\n"));
}

void cb_hide_result_window(GtkWidget *, gpointer user_data)
{
	/* Shows everything declared before */
	gtk_widget_hide_all((static_cast<t_WindowList*>(user_data))->result.window);
	fprinttextview(&((static_cast<t_WindowList*>(user_data))->main),(gchar*)_("**\tClosing Results window\t**\n"));
}

void cb_save_window(GtkWidget *, gpointer user_data)
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

void cb_start_parsing(GtkWidget *, gpointer user_data)
{
	int vTest = 0;
	if(static_cast<t_toolbox*>(user_data)->FileOpened)
	{
		fprinttextview(&((static_cast<t_toolbox*>(user_data))->WindowList.main),(gchar*)"\nParsing started...\n************************\n");
		vTest = fParseFile(&((static_cast<t_toolbox*>(user_data))->WindowList.main),static_cast<t_toolbox*>(user_data));
		fprinttextview(&((static_cast<t_toolbox*>(user_data))->WindowList.main),(gchar*)"\nParsing finished...\n************************\n");
		if(!vTest)
		{
			fprinttextview(&((static_cast<t_toolbox*>(user_data))->WindowList.main),(gchar*)"The parser detected some errors.\n");
		}
		else
		{
			int i = 0;
			/* Translators: leave %d, \n as they are formatting characters */
			gtk_combo_box_remove_text (GTK_COMBO_BOX((static_cast<t_toolbox*>(user_data))->WindowList.main.combobox),0);
			fprinttextview(&((static_cast<t_toolbox*>(user_data))->WindowList.main),(gchar*)g_strdup_printf(_("Found %d calculations\n"),(static_cast<t_toolbox*>(user_data))->NBCalculations));
			for(i=0;i<(static_cast<t_toolbox*>(user_data))->NBCalculations;i++)
			{
				gtk_combo_box_insert_text(GTK_COMBO_BOX((static_cast<t_toolbox*>(user_data))->WindowList.main.combobox),i,(gchar*)((static_cast<t_toolbox*>(user_data))->CalculationList+i)->name);
			}
			gtk_combo_box_set_active(GTK_COMBO_BOX((static_cast<t_toolbox*>(user_data))->WindowList.main.combobox),0);
		}
	}
	else
		fprinttextview(&((static_cast<t_toolbox*>(user_data))->WindowList.main),(gchar*)"No file selected.\n");
}

/* EOF */
