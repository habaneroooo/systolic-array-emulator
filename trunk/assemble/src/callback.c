#include <stdio.h>
#include <stdlib.h>

#include "../include/types.h"
#include "../include/parser.h"
#include "../include/interface.h"
#include "../include/script.h"
#include "../include/gettext.h"
#include "../include/callback.h"
#include "../include/systolic.h"
#include "../include/image.h"


void cb_quit (GtkWidget*, gpointer user_data)
{
	if(POINTER_TO_TOOLBOX->iShowed == TRUE)
	{
		free(POINTER_TO_TOOLBOX->WindowList.result.image_proc);
#if SHOW_REGISTERS_IN_RESULT_WINDOW
		free(POINTER_TO_TOOLBOX->WindowList.result.entry);
#else
		free(POINTER_TO_TOOLBOX->WindowList.result.image_reg_right);
		free(POINTER_TO_TOOLBOX->WindowList.result.image_reg_down);
#endif
	}
	//pthread_exit(NULL);
	gtk_main_quit();
}

void cb_input_file_button (GtkWidget *, gpointer user_data)
{
	t_WindowList p_WindowsList = POINTER_TO_TOOLBOX->WindowList;
	POINTER_TO_TOOLBOX->FileOpened  = 1;
}

void cb_clear_textview_button(GtkWidget *, gpointer user_data)
{
	gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW((static_cast<t_WindowList*>(user_data))->main.textview))," ",0);
}

void cb_show_result_window(GtkWidget *, gpointer user_data)
{
	if((POINTER_TO_TOOLBOX->iParsed) == TRUE)
	{
		gint row, col;
		gint chosen_calculation = gtk_combo_box_get_active(GTK_COMBO_BOX(POINTER_TO_TOOLBOX->WindowList.main.combobox));
		gint rowsize = (POINTER_TO_TOOLBOX->CalculationList+chosen_calculation)->rowsize;
		GdkPixdata sProcImage = {
			0x47646b50, /* Pixbuf magic: 'GdkP' */
			24 + 6882, /* header length + pixel_data length */
			0x2010001, /* pixdata_type */
			PROC_ROWSTRIDE,
			PROC_WIDTH,
			PROC_HEIGHT,
			PROC_RLE_PIXEL_DATA
		};

#if SHOW_REGISTERS_IN_RESULT_WINDOW == FALSE
		GdkPixdata sRightRegImage = {
			0x47646b50, /* Pixbuf magic: 'GdkP' */
			24 + 1086, /* header length + pixel_data length */
			0x2010001, /* pixdata_type */
			REG_RIGHT_ROWSTRIDE,
			REG_RIGHT_WIDTH,
			REG_RIGHT_HEIGHT,
			REG_RIGHT_RLE_PIXEL_DATA
		};
		GdkPixdata sDownRegImage = {
			0x47646b50, /* Pixbuf magic: 'GdkP' */
			24 + 1177, /* header length + pixel_data length */
			0x2010001, /* pixdata_type */
			REG_DOWN_ROWSTRIDE,
			REG_DOWN_WIDTH,
			REG_DOWN_HEIGHT,
			REG_DOWN_RLE_PIXEL_DATA
		};

		/* Memory initialization */
		POINTER_TO_TOOLBOX->WindowList.result.image_reg_right	= static_cast<GtkWidget**>(malloc(sizeof(GtkWidget*)*rowsize*rowsize));
		POINTER_TO_TOOLBOX->WindowList.result.image_reg_down	= static_cast<GtkWidget**>(malloc(sizeof(GtkWidget*)*rowsize*rowsize));
#else
		POINTER_TO_TOOLBOX->WindowList.result.entry				= static_cast<GtkWidget**>(malloc(sizeof(GtkWidget*)*rowsize*rowsize));
#endif
		POINTER_TO_TOOLBOX->WindowList.result.image_proc		= static_cast<GtkWidget**>(malloc(sizeof(GtkWidget*)*rowsize*rowsize));

		for(row = 0;row < rowsize;row++)
		{
			for(col = 0;col < rowsize;col++)
			{
				GtkWidget* p_image_proc		= *(POINTER_TO_TOOLBOX->WindowList.result.image_proc+(row*rowsize+col));

				p_image_proc = gtk_image_new_from_pixbuf(gdk_pixbuf_from_pixdata(&sProcImage,TRUE,NULL));
				gtk_container_add(GTK_CONTAINER (POINTER_TO_TOOLBOX->WindowList.result.right_fixed),p_image_proc);
				gtk_fixed_move(GTK_FIXED(POINTER_TO_TOOLBOX->WindowList.result.right_fixed),p_image_proc,PROC_WIDTH*(col*2+1),PROC_HEIGHT*(row*2+1));

#if SHOW_REGISTERS_IN_RESULT_WINDOW == TRUE

				GtkWidget* p_entry			= *(POINTER_TO_TOOLBOX->WindowList.result.entry+(row*rowsize+col));
//				p_entry = gtk_entry_new();
				*(POINTER_TO_TOOLBOX->WindowList.result.entry+(row*rowsize+col)) = gtk_entry_new();
				gtk_entry_set_editable(GTK_ENTRY(*(POINTER_TO_TOOLBOX->WindowList.result.entry+(row*rowsize+col))),FALSE);
				gtk_container_add(GTK_CONTAINER (POINTER_TO_TOOLBOX->WindowList.result.right_fixed),*(POINTER_TO_TOOLBOX->WindowList.result.entry+(row*rowsize+col)));
				gtk_widget_set_size_request(*(POINTER_TO_TOOLBOX->WindowList.result.entry+(row*rowsize+col)),2*PROC_WIDTH,PROC_HEIGHT/2);
				gtk_fixed_move(GTK_FIXED(POINTER_TO_TOOLBOX->WindowList.result.right_fixed),*(POINTER_TO_TOOLBOX->WindowList.result.entry+(row*rowsize+col)),PROC_WIDTH*(col*2)+PROC_WIDTH/2,PROC_HEIGHT*(row*2+2));
				gtk_entry_set_text(GTK_ENTRY(*(POINTER_TO_TOOLBOX->WindowList.result.entry+(row*rowsize+col))),(gchar*)"salut");

#else
				if(col < rowsize-1)
				{
					GtkWidget* p_image_reg_right= *(POINTER_TO_TOOLBOX->WindowList.result.image_reg_right+(row*rowsize+col));
					p_image_reg_right = gtk_image_new_from_pixbuf(gdk_pixbuf_from_pixdata(&sRightRegImage,TRUE,NULL));
					gtk_container_add(GTK_CONTAINER (POINTER_TO_TOOLBOX->WindowList.result.right_fixed),p_image_reg_right);
					gtk_fixed_move(GTK_FIXED(POINTER_TO_TOOLBOX->WindowList.result.right_fixed),p_image_reg_right,PROC_WIDTH*(col*2+2),PROC_HEIGHT*(row*2+1));
				}

				if(row < rowsize-1)
				{
					GtkWidget* p_image_reg_down	= *(POINTER_TO_TOOLBOX->WindowList.result.image_reg_down+(row*rowsize+col));
					p_image_reg_down = gtk_image_new_from_pixbuf(gdk_pixbuf_from_pixdata(&sDownRegImage,TRUE,NULL));
					gtk_container_add(GTK_CONTAINER (POINTER_TO_TOOLBOX->WindowList.result.right_fixed),p_image_reg_down);
					gtk_fixed_move(GTK_FIXED(POINTER_TO_TOOLBOX->WindowList.result.right_fixed),p_image_reg_down,PROC_WIDTH*(col*2+1),PROC_HEIGHT*(row*2+2));
				}
#endif
			}
		}
		fCreateThreads(POINTER_TO_TOOLBOX,chosen_calculation);
		POINTER_TO_TOOLBOX->iShowed = TRUE;
	}
	/* Shows everything declared before */
	gtk_widget_show_all(POINTER_TO_TOOLBOX->WindowList.result.window);
	fprinttextview(&(POINTER_TO_TOOLBOX->WindowList.main),(gchar*)_("**\tOpening Results window\t**\n"));

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
	
	GtkTextIter start, end;
	GtkTextBuffer *buffer;
	FILE * p_file;

	/* Creates the "save file" dialog */
	fCreateWindow_save(&(POINTER_TO_TOOLBOX->WindowList.save));
	
	/* Shows everything declared before */
	gtk_widget_show(POINTER_TO_TOOLBOX->WindowList.save.save_file_chooser);
	
	/* Wait for a response */
	while(
		(vTest == FALSE) 
		&& 
		(vTestResponse = gtk_dialog_run(GTK_DIALOG(POINTER_TO_TOOLBOX->WindowList.save.save_file_chooser)))
		)
	{
		/* Leave this for testing purpose */
		//~ sprintf(responsetype,"RESPONSE:%d\n",vTestResponse);
		//~ fprinttextview(static_cast<t_MainWindow*>(user_data),responsetype);
		switch(vTestResponse)
		{
			case GTK_RESPONSE_ACCEPT:		p_file = fopen(gtk_file_chooser_get_filename((GtkFileChooser *)POINTER_TO_TOOLBOX->WindowList.save.save_file_chooser),"wb");
											if(p_file == NULL)
											{
												fprinttextview(&(POINTER_TO_TOOLBOX->WindowList.main),(gchar*)_("Error opening file.\nPlease check if you have proper reading access to the file/directory.\n"));
											}
											buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (POINTER_TO_TOOLBOX->WindowList.main.textview));
											gtk_text_buffer_get_bounds (buffer, &start, &end);
											fputs(gtk_text_iter_get_text (&start, &end),p_file);
											fclose(p_file);
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
	gtk_widget_destroy(POINTER_TO_TOOLBOX->WindowList.save.save_file_chooser);
}

void cb_start_parsing(GtkWidget *, gpointer user_data)
{
	gint vTest = 0;
	if(POINTER_TO_TOOLBOX->FileOpened)
	{
		fprinttextview(&(POINTER_TO_TOOLBOX->WindowList.main),(gchar*)"\nParsing started...\n************************\n");
		vTest = fParseFile(&(POINTER_TO_TOOLBOX->WindowList.main),POINTER_TO_TOOLBOX);
		fprinttextview(&(POINTER_TO_TOOLBOX->WindowList.main),(gchar*)"\nParsing finished...\n************************\n");
		if(!vTest)
		{
			fprinttextview(&(POINTER_TO_TOOLBOX->WindowList.main),(gchar*)"The parser detected some errors.\n");
		}
		else
		{
			gint i = 0;
			POINTER_TO_TOOLBOX->iParsed = TRUE;
			/* Translators: leave %d, \n as they are formatting characters */
			gtk_combo_box_remove_text (GTK_COMBO_BOX(POINTER_TO_TOOLBOX->WindowList.main.combobox),0);
			fprinttextview(&(POINTER_TO_TOOLBOX->WindowList.main),(gchar*)g_strdup_printf(_("Found %d calculations\n"),POINTER_TO_TOOLBOX->NBCalculations));
			for(i = 0;i<POINTER_TO_TOOLBOX->NBCalculations;i++)
			{
				gtk_combo_box_insert_text(GTK_COMBO_BOX(POINTER_TO_TOOLBOX->WindowList.main.combobox),i,(gchar*)(POINTER_TO_TOOLBOX->CalculationList+i)->name);
			}
			gtk_combo_box_set_active(GTK_COMBO_BOX(POINTER_TO_TOOLBOX->WindowList.main.combobox),0);
		}
	}
	else
		fprinttextview(&((POINTER_TO_TOOLBOX)->WindowList.main),(gchar*)"No file selected.\n");
}

void cb_start_execution(GtkWidget *, gpointer user_data)
{
	/* Starts the handler, gives it the program to run */
	pthread_cond_signal(&(POINTER_TO_TOOLBOX->systolic_array.depart_handler));
}

/* EOF */
