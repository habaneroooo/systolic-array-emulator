#ifndef __CALLBACK__
#define __CALLBACK__

#define BUFFER_SIZE 4
#define ROW_SIZE 4
#define POINTER_TO_FILE (static_cast<t_toolbox*>(user_data))->file

void cb_quit (GtkWidget*, gpointer);
void cb_input_file_button (GtkWidget*, gpointer);
void cb_clear_textview_button(GtkWidget *, gpointer);
void cb_show_result_window(GtkWidget *,gpointer);
void cb_save_window(GtkWidget *, gpointer);
void cb_start_parsing(GtkWidget *, gpointer);
void cb_hide_result_window(GtkWidget *,gpointer);

#endif

/* EOF */
