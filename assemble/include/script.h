#ifndef __SYSTOLIC__
#define __SYSTOLIC__

int fParseFile(t_MainWindow*,t_toolbox*);
int fGetCalculation(t_MainWindow*, t_whereami*, FILE *, int , t_tools*);
void fProcess(t_MainWindow*,FILE *, t_tools *, t_calculation *,unsigned int *);
int fParseCalculation(t_MainWindow*,FILE *,t_tools *, t_calculation*);
int fCalculation(t_MainWindow*,t_whereami *, FILE *, int, t_tools *,t_calculation * );

#endif 

/* EOF */
