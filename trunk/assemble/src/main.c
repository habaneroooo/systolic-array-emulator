#include <stdio.h>
#include <stdlib.h>

#include "../include/types.h"

#include "../include/parser.h"
#include "../include/interface.h"
#include "../include/callback.h"
#include "../include/gettext.h"

void init_gettext(void) 
{ 
    setlocale(LC_ALL, ""); 
    textdomain(PROGRAM_NAME); 
    bindtextdomain(PROGRAM_NAME, "locale"); 
}

int main(int argc, char *argv[])
{
	/* Contains everything needed by callbacks */
	t_toolbox sToolbox;
	sToolbox.FileOpened = 0;
	sToolbox.iParsed = FALSE;
	sToolbox.iShowed = FALSE;
	
	/* Initialization of gettext */
	init_gettext();

	/* Prepares the thread/GTK+ cohabitation*/
	g_thread_init(NULL);
	gdk_threads_init();
	gdk_threads_enter();
	
	/* Initialization of GTK+ */
	gtk_init(&argc, &argv);
	
	/* Settings installation */
	g_type_class_unref (g_type_class_ref (GTK_TYPE_IMAGE_MENU_ITEM));
	g_object_set(gtk_settings_get_default (), "gtk-button-images", TRUE, NULL);

	/* Result window creation */
	fCreateWindow_results(&sToolbox.WindowList.result);
	
	/* Main window creation */
	fCreateWindow_main(&sToolbox.WindowList.main);
	
	/* Callbacks linking */
	/* Translators: those aren't text */
	g_signal_connect (G_OBJECT(sToolbox.WindowList.main.window), "destroy",G_CALLBACK (cb_quit), (gpointer)&sToolbox);
	g_signal_connect (G_OBJECT(sToolbox.WindowList.main.button_close), "clicked",G_CALLBACK (cb_quit), (gpointer)&sToolbox);
	g_signal_connect (G_OBJECT(sToolbox.WindowList.main.button_file_chooser), "file-set", G_CALLBACK (cb_input_file_button), (gpointer)&sToolbox);
	g_signal_connect (G_OBJECT(sToolbox.WindowList.main.button_clear_message_window), "clicked", G_CALLBACK (cb_clear_textview_button), (gpointer)&(sToolbox.WindowList));
	g_signal_connect (G_OBJECT(sToolbox.WindowList.main.button_show_result_window), "clicked", G_CALLBACK (cb_show_result_window), (gpointer)&sToolbox);
	g_signal_connect (G_OBJECT(sToolbox.WindowList.result.button_close), "clicked", G_CALLBACK (cb_hide_result_window), (gpointer)&sToolbox.WindowList);
	g_signal_connect (G_OBJECT(sToolbox.WindowList.result.window), "destroy",G_CALLBACK (cb_hide_result_window), (gpointer)&sToolbox.WindowList);
	g_signal_connect (G_OBJECT(sToolbox.WindowList.result.button_start_execute), "clicked",G_CALLBACK (cb_start_execution), (gpointer)&sToolbox);
	g_signal_connect (G_OBJECT(sToolbox.WindowList.main.button_save_log), "clicked", G_CALLBACK (cb_save_window), (gpointer)&sToolbox);
	g_signal_connect (G_OBJECT(sToolbox.WindowList.main.button_start_parse), "clicked", G_CALLBACK (cb_start_parsing), (gpointer)&sToolbox);
	

	/* main loop */
	gtk_main ();
	gdk_threads_leave();
	
	return EXIT_SUCCESS;
}
