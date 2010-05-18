#ifndef __PARSER__
#define __PARSER__
/*
 * Function prototypes
 */
unsigned int fVerifyProcessSelector(t_MainWindow* ,t_calculation * ,char **,unsigned int,bool**);
int fVerifyProcessDeclaration(t_MainWindow *,t_tools *,char *, unsigned int, t_calculation*);
int fTestRegisterValidity(char**, t_process*,int,unsigned int*);
int fLinkTokenToFunc(char,t_list*,t_tools*);
int fgetline(FILE*, unsigned int*,char**);

#endif

/* EOF */
