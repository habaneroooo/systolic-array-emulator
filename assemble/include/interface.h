#ifndef __INTERFACE__
#define __INTERFACE__

#define LARG 800
#define HAUT 600
#define LARG_RESULT 800
#define HAUT_RESULT 600
#define LEFT_MARGIN 4
#define RIGHT_MARGIN LEFT_MARGIN
#define TOP_MARGIN 4
#define BOTTOM_MARGIN TOP_MARGIN
#define SPACE_BETWEEN_ELEMENTS 4
#define GUTTER_SIZE 100
#define LARG_BUTTONS ((LARG/2)-(SPACE_BETWEEN_ELEMENTS*3/2)-(LEFT_MARGIN))/2

void fCreateWindow_main(t_MainWindow*);
void fCreateWindow_results(t_ResultWindow*);
void fCreateWindow_save(t_SaveWindow*);
void fprinttextview(t_MainWindow* ,char*);

#endif 

/* EOF */
