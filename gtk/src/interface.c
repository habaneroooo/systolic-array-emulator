#include <gtk/gtk.h>
#include <gio/gio.h>
#include "../include/interface.h"
#include "../include/callback.h"

#define LARG 200
#define HAUT 200
void fCreateWindow_main(GdkScreen* screen)
{
	int width, height;

	GtkWidget * p_window = NULL;
	p_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(p_window), "Systolic array emulator");
	g_signal_connect (G_OBJECT (p_window), "destroy",	G_CALLBACK (cb_quit), NULL);
	
	GtkWidget * p_container_file_selector_vbox = NULL;
	p_container_file_selector_vbox = gtk_vbox_new(FALSE,0);
	gtk_container_add (GTK_CONTAINER (p_window), p_container_file_selector_vbox);
	
	GtkWidget * p_label = NULL;
	p_label = gtk_label_new("Selected file: none yet");
	gtk_container_add(GTK_CONTAINER (p_container_file_selector_vbox), p_label);
	
	GtkWidget * p_file_chooser = fCreateWidget_File_chooser(screen);
	
	GtkWidget * p_button_file_chooser = NULL;
	p_button_file_chooser = gtk_file_chooser_button_new_with_dialog(p_file_chooser);
	gtk_container_add(GTK_CONTAINER (p_container_file_selector_vbox), p_button_file_chooser);
	g_signal_connect (G_OBJECT (p_file_chooser), "response", G_CALLBACK (cb_input_file_button), NULL);
	
	
	width = gdk_screen_get_width(screen);
	height = gdk_screen_get_height(screen);
	gtk_window_move(GTK_WINDOW(p_window),width/2-LARG/2,height/2-HAUT/2);
	gtk_window_resize(GTK_WINDOW(p_window), LARG, HAUT);
	
	/* Affichage de la fenetre principale */
	gtk_widget_show_all(p_window);
}

GtkWidget* fCreateWidget_File_chooser(GdkScreen* screen)
{
	GtkWidget * p_file_selector = NULL;
	
	/* Open mode */
	p_file_selector = gtk_file_chooser_dialog_new("Select source file...", NULL, GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL);
	
	/* Can't create directories */
	//~ gtk_file_chooser_set_create_folders( (GtkFileChooser *) p_file_selector, FALSE);
	
	(void)screen;
	return p_file_selector;
}

/* EOF */
