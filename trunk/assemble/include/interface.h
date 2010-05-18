#ifndef __INTERFACE__
#define __INTERFACE__

#define LARG 800
#define HAUT 600
#define WIDTH_RESULT 800
#define HEIGHT_RESULT 600
#define LEFT_MARGIN 4
#define RIGHT_MARGIN LEFT_MARGIN
#define TOP_MARGIN 4
#define BOTTOM_MARGIN TOP_MARGIN
#define SPACE_BETWEEN_ELEMENTS 4
#define GUTTER_SIZE 150
#define LARG_BUTTONS (LARG-SPACE_BETWEEN_ELEMENTS-LEFT_MARGIN-RIGHT_MARGIN)		*	(0.333)
#define HEIGHT_BUTTONS (HAUT-TOP_MARGIN-BOTTOM_MARGIN-SPACE_BETWEEN_ELEMENTS)	*	(0.05)

void fCreateWindow_main(t_MainWindow*);
void fCreateWindow_results(t_ResultWindow*);
void fCreateWindow_save(t_SaveWindow*);
void fprinttextview(t_MainWindow* ,char*);

#endif 

/* EOF */
