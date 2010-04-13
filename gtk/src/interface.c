#include <gtk/gtk.h>
#include <gio/gio.h>
#include "../include/interface.h"
#include "../include/callback.h"

#define LARG 800
#define HAUT 600
#define LEFT_MARGIN 5
#define RIGHT_MARGIN 5
#define TOP_MARGIN 5
#define BOTTOM_MARGIN 5
#define INITIAL_TEXT "Welcome to the systolic array simulator program\n"
void fCreateWindow_main(GdkScreen* screen)
{
	int width, height;

	/* Main window creation */
	GtkWidget * p_window = NULL;
	p_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(p_window), "Systolic array emulator");
	gtk_window_set_default_size(GTK_WINDOW(p_window),LARG,HAUT);
	width = gdk_screen_get_width(screen);
	height = gdk_screen_get_height(screen);
	gtk_window_move(GTK_WINDOW(p_window),width/2-LARG/2,height/2-HAUT/2);
	g_signal_connect (G_OBJECT (p_window), "destroy",G_CALLBACK (cb_quit), NULL);
	
	/* "Fixed" container creation */
	GtkWidget * p_container_fixed = NULL;
	p_container_fixed = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(p_window),p_container_fixed);
	gtk_widget_show(p_container_fixed);
	
	/* Frame creation */
	GtkWidget * p_container_frame = NULL;
	p_container_frame = gtk_frame_new("Message window");
	gtk_widget_show(p_container_frame);
	gtk_fixed_put(GTK_FIXED(p_container_fixed),p_container_frame,LEFT_MARGIN,TOP_MARGIN);
	gtk_widget_set_size_request(p_container_frame,LARG/2,HAUT*2/3);
	
	/* Scrolling bars creation */
	GtkWidget * p_container_scrolled_window = NULL;
	p_container_scrolled_window = gtk_scrolled_window_new(NULL,NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(p_container_scrolled_window),GTK_POLICY_NEVER,GTK_POLICY_AUTOMATIC);
	gtk_container_add(GTK_CONTAINER(p_container_frame),p_container_scrolled_window);
		
	/* Console window creation */
	GtkWidget * p_textview = NULL;
	GtkWrapMode wrapmode = GTK_WRAP_WORD_CHAR;
	p_textview = gtk_text_view_new();
	gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(p_textview)),INITIAL_TEXT,-1);
	gtk_text_view_set_border_window_size(GTK_TEXT_VIEW(p_textview),GTK_TEXT_WINDOW_LEFT,LEFT_MARGIN);
	gtk_text_view_set_border_window_size(GTK_TEXT_VIEW(p_textview),GTK_TEXT_WINDOW_RIGHT,RIGHT_MARGIN);
	gtk_text_view_set_border_window_size(GTK_TEXT_VIEW(p_textview),GTK_TEXT_WINDOW_TOP,TOP_MARGIN);
	gtk_text_view_set_border_window_size(GTK_TEXT_VIEW(p_textview),GTK_TEXT_WINDOW_BOTTOM,BOTTOM_MARGIN);
	gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(p_textview),0);
	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(p_textview),wrapmode);
	gtk_container_add(GTK_CONTAINER(p_container_scrolled_window),p_textview);
		
	/* File chooser dialog creation */
	GtkWidget * p_file_chooser = fCreateWidget_File_chooser(screen);
	
	/* File chooser button creation */
	GtkWidget * p_button_file_chooser = NULL;
	p_button_file_chooser = gtk_file_chooser_button_new_with_dialog(p_file_chooser);
	gtk_container_add(GTK_CONTAINER (p_container_fixed), p_button_file_chooser);
	g_signal_connect (G_OBJECT(p_file_chooser), "response", G_CALLBACK (cb_input_file_button), (gpointer)p_textview);
	gtk_fixed_move(GTK_FIXED(p_container_fixed),p_button_file_chooser,LEFT_MARGIN,HAUT*2/3+30);
	gtk_widget_set_size_request(p_button_file_chooser,LARG/2,32);
	
	/* Expander creation with 2 children and a grand child */
	//~ GtkWidget * p_ex
	
	/* Shows everything declared before */
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
