#include "../include/interface.h"

void fCreateWindow_main(t_MainWindow * s_MainWindow)
{
	int width, height;
	
	GdkScreen* screen = gdk_screen_get_default ();
	/* Main window creation */
	s_MainWindow->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(s_MainWindow->window), PROGRAM_NAME);
	gtk_window_set_default_size(GTK_WINDOW(s_MainWindow->window),LARG,HAUT);
	width = gdk_screen_get_width(screen);
	height = gdk_screen_get_height(screen);
	gtk_window_move(GTK_WINDOW(s_MainWindow->window),width/2-LARG/2,height/2-HAUT/2);
	
	/* "Fixed" container creation */
	s_MainWindow->fixed = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(s_MainWindow->window),s_MainWindow->fixed);
	gtk_widget_show(s_MainWindow->fixed);
	
	/* Frame creation */
	s_MainWindow->frame = gtk_frame_new(_("Message window"));
	gtk_widget_show(s_MainWindow->frame);
	gtk_fixed_put(GTK_FIXED(s_MainWindow->fixed),s_MainWindow->frame,LEFT_MARGIN,TOP_MARGIN);
	gtk_widget_set_size_request(s_MainWindow->frame,LARG/2-LEFT_MARGIN-SPACE_BETWEEN_ELEMENTS/2,HAUT*2/3);
	
	/* Scrolling bars creation */
	s_MainWindow->scrolled_window = gtk_scrolled_window_new(NULL,NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(s_MainWindow->scrolled_window),GTK_POLICY_NEVER,GTK_POLICY_AUTOMATIC);
	gtk_container_add(GTK_CONTAINER(s_MainWindow->frame),s_MainWindow->scrolled_window);
		
	/* Console window creation */
	GtkWrapMode wrapmode = GTK_WRAP_WORD_CHAR;
	s_MainWindow->textview = gtk_text_view_new();
	gtk_text_buffer_set_text(	gtk_text_view_get_buffer(GTK_TEXT_VIEW(s_MainWindow->textview)),
						_("Welcome to the systolic array simulator program\n"),
						-1
	);
	gtk_text_view_set_border_window_size(GTK_TEXT_VIEW(s_MainWindow->textview),GTK_TEXT_WINDOW_LEFT,LEFT_MARGIN);
	gtk_text_view_set_border_window_size(GTK_TEXT_VIEW(s_MainWindow->textview),GTK_TEXT_WINDOW_RIGHT,RIGHT_MARGIN);
	gtk_text_view_set_border_window_size(GTK_TEXT_VIEW(s_MainWindow->textview),GTK_TEXT_WINDOW_TOP,TOP_MARGIN);
	gtk_text_view_set_border_window_size(GTK_TEXT_VIEW(s_MainWindow->textview),GTK_TEXT_WINDOW_BOTTOM,BOTTOM_MARGIN);
	gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(s_MainWindow->textview),0);
	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(s_MainWindow->textview),wrapmode);
	gtk_container_add(GTK_CONTAINER(s_MainWindow->scrolled_window),s_MainWindow->textview);
		
	/* File chooser dialog creation */
	s_MainWindow->file_chooser =	gtk_file_chooser_dialog_new(_("Select source file..."), NULL, 
									GTK_FILE_CHOOSER_ACTION_OPEN,
									GTK_STOCK_CANCEL,
									GTK_RESPONSE_CANCEL,
									GTK_STOCK_OPEN,
									GTK_RESPONSE_ACCEPT,
									NULL
								);
	
	/* File chooser button creation */
	s_MainWindow->button_file_chooser = gtk_file_chooser_button_new_with_dialog(s_MainWindow->file_chooser);
	gtk_container_add(GTK_CONTAINER (s_MainWindow->fixed), s_MainWindow->button_file_chooser);
	gtk_fixed_move(GTK_FIXED(s_MainWindow->fixed),s_MainWindow->button_file_chooser,LARG-RIGHT_MARGIN-LARG_BUTTONS*2-SPACE_BETWEEN_ELEMENTS,TOP_MARGIN+30);
	gtk_widget_set_size_request(s_MainWindow->button_file_chooser,LARG_BUTTONS,30);
	
	/* File chooser button creation */
	s_MainWindow->button_file_chooser = gtk_file_chooser_button_new_with_dialog(s_MainWindow->file_chooser);
	gtk_container_add(GTK_CONTAINER (s_MainWindow->fixed), s_MainWindow->button_file_chooser);
	gtk_fixed_move(GTK_FIXED(s_MainWindow->fixed),s_MainWindow->button_file_chooser,LARG-RIGHT_MARGIN-LARG_BUTTONS*2-SPACE_BETWEEN_ELEMENTS,TOP_MARGIN+30);
	gtk_widget_set_size_request(s_MainWindow->button_file_chooser,LARG_BUTTONS,30);
	
	/* Clear message window button creation */
	s_MainWindow->button_clear_message_window = gtk_button_new_with_label(_("Clear message window"));
	gtk_widget_set_size_request(s_MainWindow->button_clear_message_window,LARG_BUTTONS,30);
	gtk_container_add(GTK_CONTAINER (s_MainWindow->fixed), s_MainWindow->button_clear_message_window);
	gtk_fixed_move(GTK_FIXED(s_MainWindow->fixed),s_MainWindow->button_clear_message_window,LEFT_MARGIN,HAUT*2/3+30);
	
	/* Save log button creation */
	s_MainWindow->button_save_log = gtk_button_new_with_label(_("Save log to file..."));
	gtk_container_add(GTK_CONTAINER (s_MainWindow->fixed), s_MainWindow->button_save_log);
	gtk_fixed_move(GTK_FIXED(s_MainWindow->fixed),s_MainWindow->button_save_log,LEFT_MARGIN+SPACE_BETWEEN_ELEMENTS+LARG_BUTTONS,HAUT*2/3+30);
	gtk_widget_set_size_request(s_MainWindow->button_save_log,LARG_BUTTONS,30);
	
	/* Show result window button creation */
	s_MainWindow->button_show_result_window = gtk_button_new_with_label(_("Show processor matrix"));
	gtk_container_add(GTK_CONTAINER (s_MainWindow->fixed), s_MainWindow->button_show_result_window);
	//~ gtk_fixed_move(GTK_FIXED(s_MainWindow->fixed),s_MainWindow->button_show_result_window,LARG/2+SPACE_BETWEEN_ELEMENTS*3/2+LARG_BUTTONS,TOP_MARGIN+30);
	gtk_fixed_move(GTK_FIXED(s_MainWindow->fixed),s_MainWindow->button_show_result_window,LARG-RIGHT_MARGIN-LARG_BUTTONS,TOP_MARGIN+30);
	gtk_widget_set_size_request(s_MainWindow->button_show_result_window,LARG_BUTTONS,30);
	
	/* Expander creation with 2 children and a grand child */
	//~ GtkWidget * p_ex
	
	/* Shows everything declared before */
	gtk_widget_show_all(s_MainWindow->window);
}

void fCreateWindow_results(t_ResultWindow* s_ResultWindow)
{
	int width, height;
	
	GdkScreen* screen = gdk_screen_get_default ();
	
	/* Result window creation */
	s_ResultWindow->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(s_ResultWindow->window),LARG_RESULT,HAUT_RESULT);
	gtk_window_set_resizable(GTK_WINDOW(s_ResultWindow->window),FALSE);
	width = gdk_screen_get_width(screen);
	height = gdk_screen_get_height(screen);
	gtk_window_move(GTK_WINDOW(s_ResultWindow->window),width/2-LARG_RESULT/2,height/2-HAUT_RESULT/2);
	
	/* HPaned creation */
	s_ResultWindow->hpaned = gtk_hpaned_new();
	gtk_paned_set_position(GTK_PANED(s_ResultWindow->hpaned),GUTTER_SIZE);
	gtk_container_add(GTK_CONTAINER (s_ResultWindow->window), s_ResultWindow->hpaned);
	
	/* Scrolling bars creation */
	s_ResultWindow->scrolled_window = gtk_scrolled_window_new(NULL,NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(s_ResultWindow->scrolled_window),GTK_POLICY_NEVER,GTK_POLICY_AUTOMATIC);
	gtk_paned_pack2(GTK_PANED(s_ResultWindow->hpaned),s_ResultWindow->scrolled_window,FALSE,FALSE);
	
	/* "Fixed1" container creation */
	s_ResultWindow->left_fixed = gtk_fixed_new();
	gtk_paned_pack1(GTK_PANED(s_ResultWindow->hpaned),s_ResultWindow->left_fixed,FALSE,FALSE);
	
	/* "Fixed2" container creation */
	s_ResultWindow->right_fixed = gtk_fixed_new();
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(s_ResultWindow->scrolled_window),s_ResultWindow->right_fixed);
	gtk_widget_set_size_request(s_ResultWindow->right_fixed,LARG_RESULT-GUTTER_SIZE,HAUT_RESULT-60);
	
	/* close window button creation */
	s_ResultWindow->button_close = gtk_button_new_with_label(_("Close"));
	gtk_container_add(GTK_CONTAINER (s_ResultWindow->left_fixed), s_ResultWindow->button_close);
	gtk_fixed_move(GTK_FIXED(s_ResultWindow->left_fixed),s_ResultWindow->button_close,LEFT_MARGIN,HAUT_RESULT-(BOTTOM_MARGIN+30+60));
	gtk_widget_set_size_request(s_ResultWindow->button_close,GUTTER_SIZE-LEFT_MARGIN-RIGHT_MARGIN,30);
}


void fCreateWindow_save(t_SaveWindow* s_SaveWindow)
{	
	/* Save file chooser dialog creation */
	s_SaveWindow->save_file_chooser =	gtk_file_chooser_dialog_new(_("Save log to file..."), 
									NULL,
									GTK_FILE_CHOOSER_ACTION_SAVE,
									GTK_STOCK_SAVE,
									GTK_RESPONSE_ACCEPT,
									GTK_STOCK_CANCEL,
									GTK_RESPONSE_CANCEL,
									NULL
								);
	gtk_window_set_modal((GtkWindow*)s_SaveWindow->save_file_chooser,TRUE);
	gtk_dialog_set_response_sensitive((GtkDialog*)s_SaveWindow->save_file_chooser,GTK_RESPONSE_CLOSE,TRUE);
}

/* EOF */
