#ifndef __CALLBACK__
#define __CALLBACK__

#define BUFFER_SIZE 4
#define ROW_SIZE 4

void cb_quit (GtkWidget*, gpointer);
void cb_input_file_button (GtkWidget*, gpointer);
void cb_clear_textview_button(GtkWidget *, gpointer);
void cb_show_result_window(GtkWidget *,gpointer);
void cb_save_window(GtkWidget *, gpointer);
void cb_hide_result_window(GtkWidget *,gpointer);
void fprinttextview(t_MainWindow* ,char*);

#endif

/* EOF */
