#include "../include/interface.h"

void init_gettext(void) 
{ 
    setlocale(LC_ALL, ""); 
    textdomain(PROGRAM_NAME); 
    bindtextdomain(PROGRAM_NAME, "locale"); 
}

int main(int argc, char *argv[])
{
	/* Structure containing every element of the user interface */
	t_WindowList s_WindowList;
	
	/* Initialization of gettext */
	init_gettext();
	
	/* Initialization of GTK+ */
	gtk_init(&argc, &argv);
	
	/* Création des sous-fenetres */
	fCreateWindow_results(&s_WindowList.result);
	
	/* Main window creation */
	fCreateWindow_main(&s_WindowList.main);
	
	/* Callbacks linking */
	g_signal_connect (G_OBJECT(s_WindowList.main.window), "destroy",G_CALLBACK (cb_quit), NULL);
	g_signal_connect (G_OBJECT(s_WindowList.main.file_chooser), "file-activated", G_CALLBACK (cb_input_file_button), (gpointer)&s_WindowList);
	g_signal_connect (G_OBJECT(s_WindowList.main.button_clear_message_window), "clicked", G_CALLBACK (cb_clear_textview_button), (gpointer)&s_WindowList);
	g_signal_connect (G_OBJECT(s_WindowList.main.button_show_result_window), "clicked", G_CALLBACK (cb_show_result_window), (gpointer)&s_WindowList);
	g_signal_connect (G_OBJECT(s_WindowList.result.button_close), "clicked", G_CALLBACK (cb_hide_result_window), (gpointer)&s_WindowList);
	g_signal_connect (G_OBJECT(s_WindowList.result.window), "destroy",G_CALLBACK (cb_hide_result_window), (gpointer)&s_WindowList);
	g_signal_connect (G_OBJECT(s_WindowList.main.button_save_log), "clicked", G_CALLBACK (cb_save_window), (gpointer)&s_WindowList);
	
	/* Lancement de la boucle principale */
	gtk_main ();
	return EXIT_SUCCESS;
}
